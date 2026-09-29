#pragma once

class ISum : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;			// pure virtual
};

class ISubtract : public IUnknown
{
public:
	// ISubtract specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *) = 0;	// pure virtual 
};

// CLSID of SumSubtract Component {A7C939D4-8674-4AE1-94C5-5151F0C5836D}
const CLSID CLSID_SumSubtract = { 0xa7c939d4, 0x8674, 0x4ae1, 0x94, 0xc5, 0x51, 0x51, 0xf0, 0xc5, 0x83, 0x6d };

// IID of ISum Interface {BFBA6402-6377-4DAC-A82B-541456794DD0}
const IID IID_ISum = { 0xbfba6402, 0x6377, 0x4dac, 0xa8, 0x2b, 0x54, 0x14, 0x56, 0x79, 0x4d, 0xd0 };

// IID of ISubtract Interface {C82BDF78-C765-4DEE-80C4-23036D60ECD2}
const IID IID_ISubtract = { 0xc82bdf78, 0xc765, 0x4dee, 0x80, 0xc4, 0x23, 0x3, 0x6d, 0x60, 0xec, 0xd2 };

/*
GUID of IUnknown
{00000000-0000-0000-C000-000000000046}
{0x00000000, 0x0000, 0xxxx, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}
*/

/*
GUID of IClassfactory
{00000001-0000-0000-C000-000000000046}
*/