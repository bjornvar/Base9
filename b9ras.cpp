/*
 * b9ras.c
 *
 *  Created on: Mar 10, 2017
 *      Author: Bjørn Vårdal
 */

#include "b9ras.hpp"

static void
readDDRBlob(B9RAS *b9ras)
{
	int rc = 1;
	int ddrFileLength;

	/* Construct blob file name */
	char * filename = (char*)malloc(2 + sizeof(DDR_DAT_FILE)); // "./ddr.dat"
	strcpy(filename, ".");
	strcat(filename, "/");
	strcat(filename, DDR_DAT_FILE);

	/* Open the DDR data file and read it into memory - if the file is not there, do not raise an error */
	FILE *f = fopen(filename, "r");
	fseek(f, 0L, SEEK_END);
	ddrFileLength = ftell(f);
	rewind(f);

	/* Read blob */
	if ((ddrFileLength > 0) && (ddrFileLength <= 0x7FFFFFFF)) {
		void *ddrData;
		ddrData = malloc(ddrFileLength);
		b9ras->ddrData = ddrData;

		if (ddrFileLength != fread(ddrData, 1, ddrFileLength, f)) {
			fprintf(stderr, "Error reading blob.\n\tError: %d\n\tEOF: %d\n", ferror(f), feof(f));
			free(filename);
			fclose(f);
			exit(-1);
		}
	}
	fclose(f);
	free(filename);
}

B9RAS *
initializeJ9RAS(ExecutionContext const *b9context)
{
	B9RAS *rasStruct = (B9RAS *)malloc(sizeof(B9RAS));

	memset(rasStruct, 0, sizeof(B9RAS));
	strcpy((char*)rasStruct->eyecatcher, "J9VMRAS");
	rasStruct->bitpattern1 = 0xaa55aa55;
	rasStruct->bitpattern2 = 0xaa55aa55;
	rasStruct->version = VERSION;
	rasStruct->length = sizeof(B9RAS);
	rasStruct->vm = (UDATA)b9context;
	rasStruct->mainThreadOffset = 0;
	rasStruct->omrthreadNextOffset = 0;
	rasStruct->osthreadOffset = 0;
	rasStruct->idOffset = 0;
	rasStruct->typedefs = 0;
	rasStruct->env = 0;
	rasStruct->buildID = 0;
	rasStruct->environment = 0;
	rasStruct->cpus = 1;
	rasStruct->memory = 1;
	strcpy((char*)rasStruct->osversion, "unknown");
	strcpy((char*)rasStruct->osarch, "unknown");
	strcpy((char*)rasStruct->osname, "unknown");
	rasStruct->pid = (UDATA)getpid();
	rasStruct->tid = (UDATA)getpid();

	readDDRBlob(rasStruct);

	return rasStruct;
}
