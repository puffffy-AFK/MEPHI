#pragma once

template <class T> class Collection {
public:
    virtual T Get(int) const = 0;
	virtual int GetLength() const = 0;
};
