/*
// File: CardSet_T.cpp
// Author: Ruoyao Wen ruoyao@wustl.edu, Wanzhou Liu l.wanzhou@wustl.edu, Zherui Zhou zherui@wustl.edu
// Purpose: Implentation of template structure: cardset.
*/
#include "CardSet_T.h"
#include <iostream>


template<typename R, typename S>
void CardSet<R, S>::print(std::ostream& os, size_t linesize)
{
	size_t index = 0;
	typename std::vector< Card<R, S> >::iterator iter = myCardSet.begin();
	for (; iter != myCardSet.end(); ++iter)
	{
		index++;
		os << (*iter) << " ";
		if (index % linesize == 0) {
			os << std::endl;
		}
	}
}
