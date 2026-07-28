#include "lib/eml.h"

int main() {
	eml::ln(eml::X).println();
	eml::exp(eml::X).println();
	eml::NEGATIVE_ONE.println();
	eml::NEGATIVE_ONE.println0();
	eml::NEGATIVE_ONE.println();
	eml::NEGATIVE_ONE.println0();
	eml::ZERO.println();
	eml::E.println();
	eml::eml{eml::ln(eml::E), eml::E}.println();
	eml::unsafe_minus(eml::X, eml::X).println();
	return 0;
}
