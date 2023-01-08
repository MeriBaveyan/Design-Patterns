//From my course project.

//PlayingSudoku.h
class PlayingSudoku
{
public:
    PlayingSudoku(PlayingSudoku& other) = delete;

    void operator=(const PlayingSudoku&) = delete;

    static PlayingSudoku* GetInstance(std::vector<std::vector<std::vector<int>>>);

    std::vector<std::vector<int>> GetPlayingMatrix();
    std::vector<std::vector<int>> GetOriginalMatrix();

    void SetPlayingMatrix(std::vector<std::vector<int>> vector);


protected:
    static PlayingSudoku* m_playingSudoku;
    std::vector<std::vector<int>> m_bigMatrixOriginal;
    std::vector<std::vector<int>> m_bigMatrixChangable;
    PlayingSudoku(std::vector<std::vector<std::vector<int>>> matrixes);
};

//PlayingSudoku.cpp
PlayingSudoku::PlayingSudoku(std::vector<std::vector<std::vector<int>>> matrixes)
{
    int size = matrixes[0].size();
    int sqrSize = sqrt(size);
    int k = 0;
    for (int i = 0; i < size - sqrSize; ++i) {
        m_bigMatrixOriginal.push_back(std::vector<int>(0));
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[0][i][j]);
        }
        for (int j = 0; j < sqrSize; ++j) {
            m_bigMatrixOriginal[k].push_back(0);
        }
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[3][i][j]);
        }
        ++k;
    }

    for (int i = size - sqrSize; i < size; ++i) {
        m_bigMatrixOriginal.push_back(std::vector<int>(0));
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[0][i][j]);
        }
        for (int j = sqrSize; j < size - sqrSize; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[2][i - size + sqrSize][j]);
        }
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[3][i][j]);
        }
        ++k;
    }

    for (int i = sqrSize; i < size - sqrSize; ++i) {
        m_bigMatrixOriginal.push_back(std::vector<int>(0));
        for (int j = 0; j < size - sqrSize; ++j) {
            m_bigMatrixOriginal[k].push_back(0);
        }
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[2][i][j]);
        }
        for (int j = 0; j < size - sqrSize; ++j) {
            m_bigMatrixOriginal[k].push_back(0);
        }
        ++k;
    }

    for (int i = 0; i < sqrSize; ++i) {
        m_bigMatrixOriginal.push_back(std::vector<int>(0));
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[4][i][j]);
        }
        for (int j = sqrSize; j < size - sqrSize; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[2][i + size - sqrSize][j]);
        }
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[1][i][j]);
        }
        ++k;
    }

    for (int i = sqrSize; i < size; ++i) {
        m_bigMatrixOriginal.push_back(std::vector<int>(0));
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[4][i][j]);
        }
        for (int j = 0; j < sqrSize; ++j) {
            m_bigMatrixOriginal[k].push_back(0);
        }
        for (int j = 0; j < size; ++j) {
            m_bigMatrixOriginal[k].push_back(matrixes[1][i][j]);
        }
        ++k;
    }

    //delete
    int matrixSize = m_bigMatrixOriginal.size();
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << m_bigMatrixOriginal[i][j] << " ";
        }
        std::cout << std::endl;
    }
    //
    m_bigMatrixChangable = m_bigMatrixOriginal;
}

std::vector<std::vector<int>> PlayingSudoku::GetPlayingMatrix()
{
    return m_bigMatrixChangable;
}

std::vector<std::vector<int>> PlayingSudoku::GetOriginalMatrix()
{
    return m_bigMatrixOriginal;
}

void PlayingSudoku::SetPlayingMatrix(std::vector<std::vector<int>> vector)
{
    m_bigMatrixChangable = vector;
}

PlayingSudoku* PlayingSudoku::m_playingSudoku = nullptr;

PlayingSudoku* PlayingSudoku::GetInstance(std::vector<std::vector<std::vector<int>>> matrixes)
{
    if (m_playingSudoku == nullptr) {
        m_playingSudoku = new PlayingSudoku(matrixes);
    }
    return m_playingSudoku;
}
