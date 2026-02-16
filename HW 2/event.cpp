//QUESTION 1
// What you'll turn in for this problem will be a file named event.cpp containing the definitions and implementations of the
//four classes, and nothing more.


//Event Class
class Event
{
private:
    string m_name;

public:     
    //constructor, string parameter, must be useful parameter 
    Event(string name) : m_name(name) {};
    string name() const { return m_name; };
    virtual string need() const = 0; 
    virtual bool isSport() const = 0; 
    virtual ~Event() {}; 
};




//BasketballGame Class 
class BasketballGame : public Event 
{
private:
    string m_name;

public: 
    BasketballGame(string name) : Event(name) {};
    virtual string need() const { return "hoops"; };
    virtual bool isSport() const { return true;  };
    virtual ~BasketballGame()
    {
        cout << "Destroying the " << name() << " basketball game" << endl; 
    }
};




//Hockey CLass 
class HockeyGame : public Event
{
private:
    string m_name;

public:
    HockeyGame(string name) : Event(name) {};
    virtual string need() const { return "ice"; };
    virtual bool isSport() const { return true; };
    virtual ~HockeyGame()
    {
        cout << "Destroying the " << name() << " hockey game" << endl;
    }
};




//Concert Class
class Concert : public Event 
{
private:
    string m_name;
    string m_type;

public:
    Concert(string name, string type) : Event(name), m_type(type) {};
    virtual string need() const { return "a stage"; };
    virtual bool isSport() const { return false; };
    virtual ~Concert()
    {
        cout << "Destroying the " << name() << " " << m_type << " concert" << endl;
    }
};


