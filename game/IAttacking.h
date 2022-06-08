#ifndef IATTTACKING_H
#define IATTACKING_H

class IAttacking {
protected:
	bool attacking = false;
public:
	virtual void Attack() = 0;
};

#endif // !IATTTACKING_H
