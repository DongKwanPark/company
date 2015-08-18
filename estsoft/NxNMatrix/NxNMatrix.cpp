// NxNMatrix.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
	Solution();
	virtual ~Solution();

	void Solve(wstring strInput);

private:
	typedef vector<TCHAR> rowData;
	vector<rowData> m_vMatrix;
	enum SEARCHFLAG { RIGHT, DOWN, LEFT };

	void InitMatrix(wstring strInput);
	int GetMaxArea();
	int Search(SEARCHFLAG eFlag, size_t nRow, size_t nCol, size_t nMoveRow, size_t nMoveCol, int& nValue);
};

Solution::Solution()
{
}

Solution::~Solution()
{
}

void Solution::Solve(wstring strInput)
{
	InitMatrix( strInput );
	int nMaxArea = GetMaxArea();

	wcout << _T("=== Output ===") << endl;
	cout << nMaxArea << endl;
}

void Solution::InitMatrix(wstring strInput)
{
	m_vMatrix.clear();
	int nIndex = 0, nPosition = 0;
	while( nPosition >= 0 )
	{
		rowData data;
		nPosition = strInput.find( _T("\\n"), nIndex );
		if( nPosition >= 0 )
		{
			for( int i = nIndex; i < nPosition; i++ )
				data.push_back( strInput.at( i ) );
			m_vMatrix.push_back( data );
			nIndex = nPosition + 2;
		}
	}
}

int Solution::GetMaxArea()
{
	int nResult = 0;
	size_t nRowSize = m_vMatrix.size();
	for( size_t i = 0; i < nRowSize; i ++ )
	{
		size_t nColSize = m_vMatrix[ i ].size();
		for( size_t j = 0; j < nColSize; j++ )
		{
			if( m_vMatrix[ i ][ j ] == _T('1') )
			{
				int nValue = 0, nSubArea = 0;
				nSubArea = Search( RIGHT, i, j, i, j, nValue );
				if( nSubArea > nResult )
					nResult = nSubArea;
			}
		}
	}
	return nResult;
}

int Solution::Search(SEARCHFLAG eFlag, size_t nRow, size_t nCol, size_t nMoveRow, size_t nMoveCol, int& nValue)
{
	int nResult = 0;
	switch( eFlag )
	{
		case RIGHT : 
			{
				size_t nColSize = m_vMatrix[ nCol ].size();
				if( nColSize > nMoveCol )
				{
					if( m_vMatrix[ nRow ][ nMoveCol ] == _T('1') )
					{
						nResult = Search( RIGHT, nRow, nCol, nMoveRow, nMoveCol + 1, nValue );
						Search( DOWN, nRow, nCol, nMoveRow, nMoveCol, nValue );
						if( nResult <= nValue )
							nResult = nValue;
						nValue = 0;
					}
				}
			}
			break;
		case DOWN :
			{
				size_t nRowSize = m_vMatrix.size();
				if( nRowSize > nMoveRow )
				{
					if( m_vMatrix[ nMoveRow ][ nMoveCol ] == _T('1') )
					{
						Search( DOWN, nRow, nCol, nMoveRow + 1, nMoveCol, nValue );
						Search( LEFT, nRow, nCol, nMoveRow, nMoveCol, nValue );
					}
				}
			}
			break;
		case LEFT :
			{
				for( int nIndex = (int)nMoveCol; nIndex >= (int)nCol; nIndex-- )
				{
					if( m_vMatrix[ nMoveRow ][ nIndex ] != _T('1') )
					{
						nValue = 0;
						break;
					}
					nValue++;
				}
			}
			break;
	}
	return nResult;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Solution solution;
	solution.Solve( argv[argc - 1] );	// -> 3
	solution.Solve( _T("0110\\n1111\\n0110\\n0100\\n") );	// -> 6
	solution.Solve( _T("1011010\\n1011111\\n1011100\\n1011101\\n1001101\\n1001100\\n1110111\\n") );	// -> 10
	solution.Solve( _T("11111\\n11111\\n11111\\n11111\\n11111\\n") );	// -> 25

	return 0;
}

