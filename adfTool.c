#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define null NULL

FILE *safeOpen(char *filename);
FILE *safeWrite(char *filename);
int decrypt(char *inFilename, char *outFilename);
int encrypt(char *inFilename, char *outFilename);

int main(int argc, char **argv) {
	int i, operation = -1; // -1 = unset; 0 = encryption; 1 = decryption
	char *inFilename = NULL, *outFilename = NULL;
	if (argc < 4) { printf("Bad input! Run me this way:\n%s -e inputMp3.mp3 outputAdf.adf\n%s -d inputAdf.adf outputMp3.mp3\n", argv[0], argv[0]); exit(EXIT_FAILURE); }
	for (i = 1; i < argc; ++i)
		if (strcmp(argv[i], "-e") == 0) operation = 0;
		else if (strcmp(argv[i], "-d") == 0) operation = 1;
	if (operation == -1) { printf("You need to specify the operation!\n"); exit(EXIT_FAILURE); }
	for (i = 1; i < argc; ++i) {
		char *tmp = argv[i];
		if (strstr(tmp, ".adf") != NULL) {
			if (operation == 0) outFilename = tmp;
			else if (operation == 1) inFilename = tmp;
		} else if (strstr(tmp, ".mp3") != NULL) {
			if (operation == 0) inFilename = tmp;
			else if (operation == 1) outFilename = tmp;
		}
	}
	if (inFilename == NULL || outFilename == NULL) { printf("Couldn't figure out some of the filenames...\n"); exit(EXIT_FAILURE); }
	printf("*************************************\nInput: %s\nOutput: %s\nOperation: %s\n*************************************\n", inFilename, outFilename, (operation == 0) ? "encryption" : "decryption" );
	if (operation == 1) return decrypt(inFilename, outFilename);
	else if (operation == 0) return encrypt(inFilename, outFilename);
	return 0;
}

int encrypt(char *inFilename, char *outFilename) {
	FILE *inputFile = safeOpen(inFilename);
        FILE *outputFile = safeWrite(outFilename);
        long int length;
        register long int i;
        fseek(inputFile, 0, SEEK_END);
        length = ftell(inputFile);
        rewind(inputFile);
        char buffer;
        int percentage = 0, unit = length/100, currUnit = 0;
        int temporaryInt;
        for (i = 0; i < length; ++i) {
                fread(&buffer, sizeof(char), 1, inputFile);
                buffer = buffer ^ 34;
                fwrite(&buffer, sizeof(char), 1, outputFile);
                currUnit += 1;
                if (currUnit >= unit) { printf("Encrypting %3d%%\r", ++percentage); currUnit = 0; }
        }
        printf("Done.                \n");
        fclose(outputFile);
        fclose(inputFile);
        return 0;
}

int decrypt(char *inFilename, char *outFilename) {
	FILE *inputFile = safeOpen(inFilename);
	FILE *outputFile = safeWrite(outFilename);
	long int length;
	register long int i;
	fseek(inputFile, 0, SEEK_END);
	length = ftell(inputFile);
	rewind(inputFile);
	char buffer;
	int percentage = 0, unit = length/100, currUnit = 0;
	int temporaryInt;
	for (i = 0; i < length; ++i) {
		fread(&buffer, sizeof(char), 1, inputFile);
		buffer = buffer ^ 34;
		fwrite(&buffer, sizeof(char), 1, outputFile);
		currUnit += 1;
		if (currUnit >= unit) { printf("Decrypting %3d%%\r", ++percentage); currUnit = 0; }
	}
	printf("Done.                \n");
	fclose(outputFile);
	fclose(inputFile);
	return 0;
}

FILE *safeOpen(char *filename) {
	FILE *input = fopen(filename, "rb");
	if (input != NULL) return input;
	else {
		printf("Cannot open %s for reading!\n", filename);
		exit(EXIT_FAILURE);
	}
}

FILE *safeWrite(char *filename) {
	FILE *output = fopen(filename, "wb");
	if (output != NULL) return output;
	else {
		printf("Cannot open %s for writing!\n", filename);
		exit(EXIT_FAILURE);
	}
}
