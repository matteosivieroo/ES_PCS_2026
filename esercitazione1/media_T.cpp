#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc <2) {
	cerr << "Errore: file non specificato\n";
	return 1;
	}

    string filename = argv[1]; 
    ifstream ifs(filename);

    if ( ifs.is_open() ) {
        string città;
        double t1, t2, t3, t4; 

        while( !ifs.eof() ) { 

            ifs >> città >> t1 >> t2 >> t3 >> t4; 
            double media=(t1+t2+t3+t4)/4.0;
            cout << città << " " << media << "\n";
        }
    }

    else {cerr <<"Errore: impossibile aprire il file " << filename << "\n";
        return 1;
        }

return 0;
}
