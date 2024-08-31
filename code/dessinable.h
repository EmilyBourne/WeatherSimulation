#ifndef PRJ_DESSINABLE_H
#define PRJ_DESSINABLE_H
#include <iostream>

class dessinable {
	public:
	virtual void dessine (std::ostream& flot=std::cout) const = 0;

	virtual void parametre (unsigned int code_param, unsigned int changement) {}
};

#endif // PRJ_DESSINABLE_H
