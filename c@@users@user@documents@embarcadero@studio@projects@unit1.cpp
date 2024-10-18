//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <limits>
#include "Unit1.h"
//#include <vcl.h>
#include <cmath>    // For power calculations
#include <cctype>   // For character checks (isdigit, toupper)
#include <stdint.h> // For int64_t



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.NmXhdpiPh.fmx", _PLAT_ANDROID)
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
#pragma resource ("*.LgXhdpiTb.fmx", _PLAT_ANDROID)
#pragma resource ("*.LgXhdpiPh.fmx", _PLAT_ANDROID)

TNuCon *NuCon;
//---------------------------------------------------------------------------
using namespace std;

//variables
int currentBase;
String Dec,Bin,Oct,Hex;
String thisNumber, error;


String convertNumber(String number, int fromBase, int toBase);

__fastcall TNuCon::TNuCon(TComponent* Owner)
	: TForm(Owner)
{

	currentBase = 10;
}
//---------------------------------------------------------------------------

void __fastcall TNuCon::DecimalChange(TObject *Sender)
{
	currentBase = 10;
}
//---------------------------------------------------------------------------
void __fastcall TNuCon::HexadecimalChange(TObject *Sender)
{
	 currentBase = 16;
}
//---------------------------------------------------------------------------
void __fastcall TNuCon::OctalChange(TObject *Sender)
{
	currentBase = 8;
}
//---------------------------------------------------------------------------
void __fastcall TNuCon::BinaryChange(TObject *Sender)
{
	  currentBase = 2;
}
//---------------------------------------------------------------------------

void __fastcall TNuCon::convertClick(TObject *Sender)
{

		thisNumber = Input->Text;

	   // Ensure currentBase is a valid integer between 2 and 36
if (!thisNumber.IsEmpty()) {
	try {
		Bin = convertNumber(thisNumber, currentBase, 2);  // Convert to binary
        Dec = convertNumber(thisNumber, currentBase, 10);  // Convert to decimal
        Oct = convertNumber(thisNumber, currentBase, 8);  // Convert to octal
		Hex = convertNumber(thisNumber, currentBase, 16);  // Convert to hexadecimal

		outDec->Text = Dec;
        outHex->Text = Hex;
		outBinary->Text = Bin;
        outOctal->Text = Oct;

        outError->Text = "";
    } catch (const Exception &e) {
        // Display any potential errors
        outError->Text = "Error: " + String(e.Message);
    }
} else {
    outError->Text = "Invalid input or base!";
}

}
//---------------------------------------------------------------------------


String convertNumber(String number, int fromBase, int toBase) {
	// Check if the bases are valid (between 2 and 36)
	if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36) {
		return "Invalid base";
	}

    // Step 1: Convert the input number (in 'fromBase') to a decimal (base 10) number
	int64_t decimalValue = 0;

	for (int i = 1; i <= number.Length(); i++) {  // 1-based indexing
		int digitValue;
		Char currentChar = number[i];  // 1-based access for characters

		// Check if the character is a digit or letter and get the digit's value
		if (isdigit(currentChar)) {
			digitValue = currentChar - '0';  // Convert character '0'-'9' to digit 0-9
		} else if (isalpha(currentChar)) {
			digitValue = toupper(currentChar) - 'A' + 10;  // Convert 'A'-'Z' to 10-35
		} else {
			return "Invalid character in input";  // Handle invalid characters
		}

		// Check if digit value is valid for the base
		if (digitValue >= fromBase) {
			return "Invalid digit for the given base";
		}

		// Convert to decimal value (manual calculation of power of the base)
		decimalValue = decimalValue * fromBase + digitValue;
	}

	// Step 2: Convert the decimal value to the target 'toBase'
    String result = "";
    if (decimalValue == 0) {
		return "0";  // Edge case: if the number is zero, return "0"
    }

	while (decimalValue > 0) {
        int remainder = decimalValue % toBase;

		// Convert the remainder to the corresponding character
        if (remainder < 10) {
			result = String((char)(remainder + '0')) + result;  // For digits 0-9
		} else {
			result = String((char)(remainder - 10 + 'A')) + result;  // For letters A-Z
		}

		decimalValue /= toBase;
	}

	return result;
}


