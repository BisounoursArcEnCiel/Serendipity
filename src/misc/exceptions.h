#include <exception>

//Levée quand on veut accéder à une case
//qui n'appartient pas à un tableau
//ex. a[i] où i > length(a)
class WrongLength: public exception
{
 public:
    WrongLength(char* const& phrase="Wrong length") throw()
	:m_phrase(phrase) {};

    virtual const char* what() const throw() {
	return m_phrase.c_str();
    };

    virtual ~WrongLength() throw() {}

 private:
    char* m_phrase;
};


//Levée quand on ne trouve pas un élément
class NotFound: public exception
{
 public:
    NotFound(char* const& phrase="Element no found.") throw()
	:m_phrase(phrase) {};

    virtual const char* what() const throw() {
	return m_phrase.c_str();
    };

    virtual ~NotFound() throw() {}

 private:
    char* m_phrase;
};

