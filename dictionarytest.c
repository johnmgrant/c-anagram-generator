#include <stdio.h>

int main()
{
	FILE* file = fopen("/usr/share/dict/american-english", "r"); /* should check the result */
	if (file == NULL) {
		printf("Error opening the dictionary\n");
		return -1;
	}

	char line[46];

	while (fgets(line, sizeof(line), file)) {
		/* note that fgets don't strip the terminating \n, checking its
		 *            presence would allow to handle lines longer that sizeof(line) */
		printf("%s", line); 
	}
	/* may check feof here to make a difference between eof and io failure -- network
	 *        timeout for instance */

	fclose(file);

	return 0;
}
