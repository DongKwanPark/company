// stackproblem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atlstr.h"
#include <iostream>
#include <vector>
using namespace std;

#define ELEMENTCOUNT 2

class CSolution
{
public:
	CSolution();
	virtual ~CSolution();

	void Run(CString strInput, CString strOutput);

private:
	typedef vector<TCHAR> StackValue;
	vector<StackValue> m_vResult;

	int m_nTrackCount;
	CString m_strInput;
	CString m_strOutput;
	TCHAR m_Element[ELEMENTCOUNT];

	void Init(CString strInput, CString strOutput);
	void Destory();
	void BackTrack(TCHAR chValue[], int nLength, int nPosition);
	bool Escape(int nLength, int nPosition);
	void Result(TCHAR chValue[], int nLength);
	int ElementCount();
	TCHAR ElementAt(int nIndex);
	bool BranchRemove(TCHAR chValue[], int nLength, int nPosition);
	void Print();
	void IncreaseTrackCount();
	int GetTrackCount();
};

CSolution::CSolution()
: m_nTrackCount( 0 )
{
}

CSolution::~CSolution()
{
	Destory();
}

void CSolution::Run(CString strInput, CString strOutput)
{
	Init( strInput, strOutput );

	int nTotalCount = strInput.GetLength() * 2;
	TCHAR* chValue = new TCHAR[ nTotalCount ];

	BackTrack( chValue, nTotalCount, 0 );

	if( chValue ) delete[] chValue;

	Print();
}

void CSolution::Init(CString strInput, CString strOutput)
{
	Destory();

	m_nTrackCount = 0;
	m_strInput = strInput;
	m_strOutput = strOutput;
	
	m_Element[ 0 ] = _T('i');
	m_Element[ 1 ] = _T('o');
}

void CSolution::Destory()
{
	m_vResult.clear();
}

void CSolution::BackTrack(TCHAR chValue[], int nLength, int nPosition)
{
	IncreaseTrackCount();
	if( Escape( nLength, nPosition ) )
	{
		Result( chValue, nLength );
	}
	else
	{
		nPosition += 1;
		for( int i = 0; i < ELEMENTCOUNT; i++ )
		{
			chValue[ nPosition - 1 ] = ElementAt( i );
			if( BranchRemove( chValue, nLength, nPosition ) )
				continue;
			BackTrack( chValue, nLength, nPosition );
		}
	}
}

bool CSolution::Escape(int nLength, int nPosition)
{
	return (bool)( nLength == nPosition );
}

void CSolution::Result(TCHAR chValue[], int nLength)
{
	StackValue stackValue;
	for( int i = 0; i < nLength; i++ )
		stackValue.push_back( chValue[ i ] );
	m_vResult.push_back( stackValue );
}

int CSolution::ElementCount()
{
	return ELEMENTCOUNT;
}

TCHAR CSolution::ElementAt(int nIndex)
{
	TCHAR chResult = _T('');
	if( nIndex < ELEMENTCOUNT )
		chResult = m_Element[ nIndex ];
	return chResult;
}

bool CSolution::BranchRemove(TCHAR chValue[], int nLength, int nPosition)
{
	bool bResult = false;
	int nPushCount = 0, nPopCount = 0;
	CString strStackValue, strResult;

	for( int i = 0; i < nPosition; i++ )
	{
		if( chValue[ i ] == ElementAt( 0 ) )
		{
			strStackValue += m_strInput[ nPushCount ];

			nPushCount++;
			if( nPushCount > ( nLength / 2 ) )
			{
				bResult = true;
				break;
			}
		}
		if( chValue[ i ] == ElementAt( 1 ) )
		{
			nPopCount++;
			if( i == 0 || nPopCount > ( nLength / 2 ) || nPopCount > nPushCount )
			{
				bResult = true;
				break;
			}
			strResult += strStackValue.GetAt( nPushCount - nPopCount );
			strStackValue.Delete( nPushCount - nPopCount );
		}
	}
 	if( bResult == false )
 	{
		if( nPosition == nLength )
		{
			if( m_strOutput != strResult )
				bResult = true;
		}

 	}

	return bResult;
}

void CSolution::Print()
{
	wcout << _T("[") << endl;
	int nTotalCount = m_vResult.size();
	for( int i = 0; i < nTotalCount; i++ )
	{
		StackValue stackValue = m_vResult[ i ];
		int nValueCount = stackValue.size();
		for( int j = 0; j < nValueCount; j++ )
			wcout << stackValue[ j ];
		wcout << endl;
	}
	wcout << _T("]") << endl;
	wcout << _T("BackTrack Call Count = ") << GetTrackCount() << endl;
}

void CSolution::IncreaseTrackCount()
{
	m_nTrackCount += 1;
}

int CSolution::GetTrackCount()
{
	return m_nTrackCount;
}


int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	CSolution solution;
 	solution.Run( _T("madam"), _T("adamm") );
 	solution.Run( _T("bahama"), _T("bahama") );
  	solution.Run( _T("long"), _T("short") );
  	solution.Run( _T("eric"), _T("rice") );
//	solution.Run( _T("abcdefgabcdefgabcdefgabcdefg"), _T("abcdefgabcdefgabcdefgabcdefg") );

	return 0;
}

