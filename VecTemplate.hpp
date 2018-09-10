//
//  VecTemplate.h
//  squishysPlugin1 - Shared Code
//
//  Created by Squishy on 27/12/2017.
//

#ifndef VecTemplate_h
#define VecTemplate_h

// USER HEADERS
#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"

#define console_log(x) std::cout << x << std::endl
//#define console_log(x)

typedef std::vector<int> Vec_Int;
typedef std::vector<float> Vec_Float;
typedef std::vector<String> Vec_String;
typedef std::vector<IIRFilter> Vec_IIR;
typedef std::vector<IIRCoefficients> Vec_IIRCoef;

#endif /* VecTemplate_h */
