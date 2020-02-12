//------------------------------------------------------------------------------
//
// File Name:	Tilemap.h
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2020 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Tilemap.h"
#include "Matrix2DStudent.h"

#include <fstream>
#include <sstream>
#include <iomanip>

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a tilemap from the given parameters.
// Params:
//   numColumns = The width of the map.
//   numRows = The height of the map.
//   data = The array containing the map data.
Tilemap::Tilemap(unsigned numColumns, unsigned numRows, int** data) : 
        m_numColumns(numColumns), m_numRows(numRows), m_data(data) {

}

// Destructor.
Tilemap::~Tilemap() {
    for (unsigned i = 0; i < m_numColumns; ++i) {
        delete[] m_data[i];
    }
    delete[] m_data;
}

// Gets the width of the map (in tiles).
unsigned Tilemap::GetWidth() const {
    return m_numColumns;
}

// Get the height of the map (in tiles).
unsigned Tilemap::GetHeight() const {
    return m_numRows;
}

// Gets the value of the cell in the map with the given indices.
// Params:
//   column = The column of the cell.
//   row = The row of the cell.
// Returns:
//   -1 if the indices are invalid, 0 if the cell is empty, 
//   or a positive integer otherwise.
int Tilemap::GetCellValue(unsigned column, unsigned row) const {
    if (column > m_numColumns || row > m_numRows)
        return -1;

    return m_data[row][column];
}

std::string Tilemap::m_mapPath = "Assets/Levels/";

// Create a tilemap from the given file.
// Params:
//   filename = The name of the file containing the tilemap data.
Tilemap* Tilemap::CreateTilemapFromFile(const std::string& filename) {
    std::stringstream sstream;
    sstream << m_mapPath << filename;
    std::string path = sstream.str();
    std::ifstream file(path);

    //check if file opened sucsessfully
    if (!file.is_open()) {
        std::cerr << "ERROR LOADING TILEMAP FROM FILE: " << path << ":" << std::endl << "CANNOT OPEN FILE" << std::endl;
        return nullptr;
    }

    int columns;
    int rows;

    if (!ReadIntegerVariable(file, "width", columns)) {
        std::cerr << "ERROR LOADING TILEMAP FROM FILE: " << path << ":" << std::endl << "WIDTH NOT FOUND" << std::endl;
        return nullptr;
    }
    if (!ReadIntegerVariable(file, "height", rows)) {
        std::cerr << "ERROR LOADING TILEMAP FROM FILE: " << path << ":" << std::endl << "HEIGHT NOT FOUND" << std::endl;
        return nullptr;
    }

    int** data = ReadArrayVariable(file, "data", (unsigned)columns, (unsigned)rows);

    if (data == nullptr) {
        std::cerr << "ERROR LOADING TILEMAP FROM FILE: " << path << ":" << std::endl << "ERROR READING DATA" << std::endl;
        return nullptr;
    }

    std::cout << "Tilemap loaded sucsessfully: " << path << ":" << std::endl;

    std::cout << "-------------------------" << std::endl;

    std::cout << "width: " << columns << std::endl;
    std::cout << "height: " << rows << std::endl;

    std::cout << "data: " << std::endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << std::left << std::setw(3) << data[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "-------------------------" << std::endl;

    return new Tilemap((unsigned)columns, (unsigned)rows, data);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Helper function for reading in values of integers.
// Params:
//   file = The file stream to read from.
//   name = The text to look for before reading the value.
//   variable = If the name is valid, the variable to put the value in.
// Returns:
//   True if a value with the given name was found, false otherwise.
bool Tilemap::ReadIntegerVariable(std::ifstream& file, const std::string& name, int& variable) {
    file.clear();
    file.seekg(0, std::ios::beg);
    std::string word;
    while (file >> word) {
        if (word == name) {
            file >> variable;
            return true;
        }
    }
    return false;
}

// Helper function for reading in arrays of integers.
// Params:
//   file = The file stream to read from.
//   name = The text to look for before reading the array.
//   columns = The number of columns in the array.
//   rows = The number of rows in the array.
// Returns:
//   A pointer to the dynamically allocated array if the data is valid, nullptr otherwise.
int** Tilemap::ReadArrayVariable(std::ifstream& file, const std::string& name, unsigned columns, unsigned rows) {
    if (columns == 0 || rows == 0)
        return nullptr;

    file.clear();
    file.seekg(0, std::ios::beg);
    std::string word;
    while (file >> word) {
        if (word == name) {

            //allocate data
            int** dat = new int* [columns];
            for (unsigned i = 0; i < columns; ++i) {
                dat[i] = new int[rows];
            }

            //read data from file and store it in dat
            for (unsigned i = 0; i < rows; ++i) {
                for (unsigned j = 0; j < columns; ++j) {
                    if (!(file >> dat[i][j])) {
                        //error
                        for (unsigned c = 0; c < columns; ++c) {
                            delete[] dat[c];
                        }
                        delete[] dat;

                        return nullptr;
                    }
                }
            }

            return dat;

        }
    }
    return nullptr;
}