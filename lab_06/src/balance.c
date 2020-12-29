#include "../inc/balance.h"

unsigned char height(tnode_t *p)
{
	return p ? p->height : 0;
}

int bfactor(tnode_t *p)
{
	return height(p->right) - height(p->left);
}

void fixheight(tnode_t *p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);

	p->height = (hl > hr ? hl : hr) + 1;
}

tnode_t *rotateright(tnode_t *p)
{
	tnode_t *q = p->left;

	p->left = q->right;
	q->right = p;

	fixheight(p);
	fixheight(q);

	return q;
}

tnode_t *rotateleft(tnode_t *q)
{
	tnode_t *p = q->right;

	q->right = p->left;
	p->left = q;

	fixheight(q);
	fixheight(p);

	return p;
}

tnode_t *balance(tnode_t *p)
{
	fixheight(p);

	if (bfactor(p) == 2)
	{
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);

		return rotateleft(p);
	}

	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);

		return rotateright(p);
	}

	return p;
}
