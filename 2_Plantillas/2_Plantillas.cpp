// 2_Plantillas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

//clase plantilla para guardar datos
template <typename T>
class DataHelper 
{
    T data;

public:
    DataHelper(T newdata)
    {
        data = newdata;
    }
    void print() 
    {
        cout << data << "\n";
    }

    //imprime al archivo dado por la ruta
    void PrinttoFile(const char* filename, bool binary = false) 
    {
 
        if (!binary)
        {
            std::fstream myfile(filename, std::ios_base::out);
            if (myfile.is_open())
            {
                myfile << sizeof(T) << data;
                
                myfile.close();
            }
            else
            {
                cout << "no se puede abrir lmao lmao" << "\n";
            }
        }
        else 
        {
            std::fstream myfile(filename, std::ios_base::out | std::ios_base::binary);
            if (myfile.is_open()) 
            {
                myfile << sizeof(T) << data;
                myfile.close();
            }
        }
    }
};

//defino lo que es un Pixel
struct Pixel {
    unsigned char blue, green, red;
};

int main()
{
    cout << "Tamaños\n";
    cout << "int : " << sizeof(int) << "\n"; //el valor deberia de ser 4 bits
    cout << "float : " << sizeof(float) << "\n"; //igual en este
    cout << "double : " << sizeof(double) << "\n"; //aqui debería de ser 8 
    cout << "char : " << sizeof(char) << "\n"; //este ocupa solo un bit
    cout << "string : " << sizeof(string) << "\n"; //el valor aqui son 40 bits siendo mucho 

    DataHelper<char>* mychar = new DataHelper<char>('w');
    DataHelper<float>* myfloat = new DataHelper<float>('3.14');

    DataHelper<char*>* mychars = new DataHelper<char*>((char*)"Hello Baby ");

    mychar->print();
    myfloat->print();
    mychars->print();

    myfloat->PrinttoFile("Float.txt");
    myfloat->PrinttoFile("Float.bin", true);

    //abrir archivo
    std::fstream archivo("Bear.bmp", std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if (archivo.is_open())
    {
        // Saltar la cabecera del archivo BMP (54 bytes)
        archivo.seekg(54);

        // Mientras no se alcance el final del archivo
        Pixel pixel;
        while (archivo.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel))) {
            // Invertir los colores del pixel
            pixel.red = 255 - pixel.red;
            pixel.green = 255 - pixel.green;
            pixel.blue = 255 - pixel.blue;

            // Mover el puntero de escritura 3 bytes hacia atrás para sobrescribir el pixel
            archivo.seekp(archivo.tellp() - std::streampos(sizeof(Pixel)));

            // Escribir el pixel modificado en el archivo
            archivo.write(reinterpret_cast<char*>(&pixel), sizeof(Pixel));

            // Mover el puntero de lectura a la posición después del pixel
            archivo.seekg(archivo.tellp());
        }
    }
    else
    {
        std::cout << "No se puede abrir el archivo." << "\n";
    }
}

