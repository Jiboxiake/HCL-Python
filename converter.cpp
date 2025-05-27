#include <iostream>
#include <fstream>
#include <string>

void processFile(std::fstream& rawfile) {
    size_t offset = 0;
    size_t label_size =0;
    rawfile.read(reinterpret_cast<char*>(&offset), sizeof(size_t));
    rawfile.read(reinterpret_cast<char*>(&label_size), sizeof(size_t));
    offset+=8;
    std::cout<<"label size is "<<label_size<<std::endl;
    for(size_t i=1; i<=label_size; i++){
        uint32_t distance_offset=0;
        rawfile.read(reinterpret_cast<char*>(&distance_offset), sizeof(uint32_t));
        offset+=4;
        if(distance_offset == 0){
            size_t data_size=0;
            rawfile.read(reinterpret_cast<char*>(&data_size), sizeof(size_t));
            offset+=8;
            char* data = new char[data_size];
            rawfile.read(data, data_size);
            offset += data_size;
            // Process the data as needed

            delete[] data;
        }else{
            uint32_t parent =0;
            rawfile.read(reinterpret_cast<char*>(&parent), sizeof(uint32_t));
            offset+=4;
        }
    }
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    const char* filename = argv[1];
    std::fstream rawfile(filename,std::ios::in | std::ios::binary);
    rawfile.close();
    return 0;
}