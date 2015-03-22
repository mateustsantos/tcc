#include "testbench.h"

bool testbench::load_vectors(const char *fname)
{
	int i, num, val;
	FILE *fp = fopen(fname, "r");

	if (!fp)
		return(false);

	cout << "Loading input vectors from '" << fname << "'" << endl;

	fscanf(fp, "%d", &num);
	num_vectors = num;

	cout << "stimuli_a = [";
	for (i = 0; i < num; i++) {
		fscanf(fp, "%d", &val);
		stimuli_a.push_back(val);
		cout << " " << val;
	}
	cout << " ]" << endl;

	cout << "stimuli_b = [";
	for (i = 0; i < num; i++) {
		fscanf(fp, "%d", &val);
		stimuli_b.push_back(val);
		cout << " " << val;
	}
	cout << " ]" << endl;

	return(true);
}

void testbench::proc()
{
	cout << "\rStimuli: " << count;

	if (count++ == num_vectors) {
		sc_stop();
		cout << endl;
	} else {
		cout << "\ta = " << stimuli_a[count-1];
		a.write(stimuli_a[count-1]);
		cout << "\tb = " << stimuli_b[count-1];
		b.write(stimuli_b[count-1]);
	}
}
