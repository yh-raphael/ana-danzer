// Date of Creation: Aug. 1, 2022
// Date of Modification: Aug. 24, 2022
// Author: Yong-hyeon Cho

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstring>
#include <unistd.h>
using namespace std;

#define MAX_LINE_SIZE   200
// #define NUM_LINE        254888
// const char* input_file_name = "tracefile-test.txt";

int main(int argc, char *argv[])
{
    string ifname;
    string ofname;
    int opt;
    while (-1 != (opt = getopt(argc, argv, "i:o:")))
    {
        switch (opt) {
           case 'i':
                ifname = optarg;
                break;
           case 'o':
                ofname = optarg;
                break;
           default:
                cerr << "Input Format Error!" << endl;
                exit(0);
        }
    }
    cout << "Input file name : " << ifname << endl;

    // time measure - start
    time_t start, finish;
    double duration;
    start = time(NULL);

    // Test code
    // cout << "hello" << endl;
    // printf("hi\n");

/*
    // TODO: file read
    FILE* fp;
    fp = fopen("dedup_trace copy.txt", "rt");

    // TODO: file
    fclose(fp);
*/

    // main start
    ifstream ifile;
    char line [MAX_LINE_SIZE];      // text buffer

    ifile.open(ifname);
    cout << "[1] Opened the input file successfully" << endl;

    int count = 0;
    vector<string> f_array;         // DS: array[n]
    vector<int> n_array;            // DS: array[n]
    unordered_map<string, int> umap;

    cout << "[2] Read and save fingerprints . . ." << endl;
    // Read file contents
    ifile.getline(line, sizeof(line));              // 1st line-> File name: /home/safdar/dedupAnalyzer/test_dir/random_1M_1K.txt, Size: 1044000000
    ifile.getline(line, sizeof(line));              // 2nd line-> Fingerprints: 
    do
    {   // Iterate per-file portions
        while (ifile.getline(line, sizeof(line)))   // number of lines: 254,888
        {                                           // 1 fingerprint size: 40 bytes
            // cout << line << endl;
            // string strr(line);
            // cout << strr.length() << endl;
            char prefix[5] = "\0";
            strncpy(prefix, line, 4);

            // cout  << prefix << endl;
            if(strcmp(prefix, "File") == 0) {                       // 1st line-> File name: /home/safdar/dedupAnalyzer/test_dir/random_1M_1K.txt, Size: 1044000000
                cout << "Just met new file contents!" << endl;
                break;
            }

            f_array.push_back(line);
            n_array.push_back(0);

            count ++;
            // if (count == 10) break;
        }
    } while (ifile.getline(line, sizeof(line)));                    // 2nd line-> Fingerprints: 
    // break once meeting EOF
    cout << "Now, end-of-the tracefile!!" << endl;

    cout << " * number of fingerprints = " << count << " * " << endl;

    cout << "[3] Hash the fingerprints each other . . ." << endl;
    // Compare fingerprints each other
    for (int i = 0; i < count; i++)
    {
        // cout << f_array[i] << endl;
        // int cur_pos = i + 1;

        // if (umap[f_array[i]] >= 1)
        umap[f_array[i]] ++;

        if (umap[f_array[i]] > 1)
            cout << i + 1 << "      " << f_array[i] << "   " << umap[f_array[i]] << endl;
    }

/*
    // Print results (dup_count)
    for (int i = 0; i < count; i++)
    {
        cout << n_array[i] << endl;
    }

    // Traversing an unordered map
    for (auto x : umap)
      cout << x.first << " " << x.second << endl;
*/

    cout << "[4] Calculating the duplicate-ratio . . ." << endl;
    int dup_count = 0;
    double dup_ratio = 0;
    // Traversing an unordered map
    for (auto x : umap)
    {
        if (x.second != 1) {
            dup_count += (x.second - 1);
        }
    }
    dup_ratio = dup_count / (double) count;

    cout << endl << "number of fingerprints:    " << count << endl;
    cout << "number of duplicates:      " << dup_count << endl;
    cout << "duplicate-ratio:           " << dup_ratio << endl;

    ifile.close();

    // time measure - finish
    finish = time(NULL);
    duration = (double) (finish - start);
    cout << endl << "elapsed time:              " << duration << " seconds" << endl;

    // Write result file
    ofstream ofile(ofname);
    if (ofile.is_open()) {
        ofile << "Input file name:           " << ifname << endl << endl;
        ofile << "number of fingerprints:    " << count << endl;
        ofile << "number of duplicates:      " << dup_count << endl;
        ofile << "duplicate-ratio:           " << dup_ratio << endl << endl;

        ofile << "elapsed time:              " << duration << " seconds" << endl;
    }
    ofile.close();

    return 0;
} 
