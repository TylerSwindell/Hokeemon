/******************************************************************************
 * C++ main.cpp     Hokeemon
 * Due Date:        04 / 24 / 2022
 * Author:          Tyler Swindell
 ******************************************************************************/
#include <iostream>	/* string, cin, cout */
#include <iomanip>	/* setw */
#include <limits>   /* std::numeric_limits */

/******************************************************************************
 * Vector Class 
******************************************************************************/
template <typename T>
class Vector {
private:
    size_t numOfEle;
    T* arr;
    
    // Bold White
    const static std::string B_W;         
    // Bold Teal
    const static std::string B_T;
    // Bold Red
    const static std::string B_R;
    // Reset Text
    const static std::string R_T;

    void resize(int ind);

public:
    Vector();
    
    size_t size();
    size_t index();
    T get(size_t index);

    void push(const T &element);
    void pop();
    void remove(size_t index);
    
    void print(bool newLine = false);    
};


template <typename T>
const std::string Vector<T>::B_W = "\033[1;37m";

template <typename T>
const std::string Vector<T>::B_T = "\033[1;36m";

template <typename T>
const std::string Vector<T>::B_R = "\033[1;31m";

template <typename T>
const std::string Vector<T>::R_T = "\033[0m";


template <typename T>
Vector<T>::Vector() {
    std::cout << "Making Vector\n";
    numOfEle = 0;
    arr = new T[0];
}

template <typename T>
// Returns size of Vector array
size_t Vector<T>::size() { return numOfEle; }

template <typename T>
// Returns last index number of the vector
size_t Vector<T>::index() { return this->size()-1; }

template <typename T>
// Used in multiple methods to resize the main pointer
// ie push() & pop()
void Vector<T>::resize(int ind) {
    numOfEle += ind;

    // Creates new array for temp item storage
    T* tempArr = new T[numOfEle];

    // Fills tempInv with the previously entered items
    if (numOfEle > 1 ) 
        for (size_t i = 0; i < numOfEle; i++) 
            tempArr[i] = arr[i];

    // Deletes the current grades pointer data
    delete[] arr;

    // Stores the tempGrades data in grades pointer
    arr = tempArr;
    tempArr = nullptr;
}


template <typename T>
// Adds an item to the end of the Vector
void Vector<T>::push(const T &element) {
    this->resize(1);

    // Adds the new item to the tempInv storage
    this->arr[numOfEle-1] = element;
}

template <typename T>
// Removes last index from vector
void Vector<T>::pop() { this->resize(-1); }

template <typename T>
// Removes last index from vector
void Vector<T>::remove(size_t index) { 
    this->resize(-1); 

}

template <typename T>
// Returns value from specific index location
T Vector<T>::get(size_t index) { return arr[index]; }

template <typename T>
// Outputs the content of the Vector to the terminal
void Vector<T>::print(bool newLine) { 
    std::cout << B_W << "[ ";
    for(size_t i = 0; i < numOfEle; i++) {
        std::cout << B_T << arr[i]; 
        if (i < numOfEle-1) 
            std::cout << B_W << ", ";
    }
    std::cout << B_W << " ]" << R_T;
    if (newLine) std::cout << '\n';
}

/******************************************************************************
 * Date Class 
******************************************************************************/
class Date {
    private:
        int month = 0, day = 0, year = 0000;
        int dateInts[3] = {month, day, year};
        std::string dateArr[5];

        static const std::string    
            BOLD_WHITE_TEXT,
            BOLD_RED_TEXT,
            TEXT_RESET,
            BRT, BWT, RTF, 
            PASSED,
            FAILED;

        void passedTest();
        void failedTest();

    public:
        Date();
        Date(int m, int d, int y);
        void setDate(int, int, int);
        int* getDate();
        void setDefaultDateTime();
        short convertMonth(std::string month);
        std::string getDateString();
        void printDate();

        void componentUnitTest();
        void testComponent(std::string, std::string);
};

const std::string 
    Date::BOLD_WHITE_TEXT = "\033[1;97m",
    Date::BOLD_RED_TEXT = "\033[1;31m",
    Date::TEXT_RESET = "\033[0m",
    Date::BWT = BOLD_WHITE_TEXT,
    Date::BRT = BOLD_RED_TEXT,
    Date::RTF = TEXT_RESET,
    Date::PASSED = BWT + "Passed\n",
    Date::FAILED = BRT + "Failed\n";



Date::Date() { 
    setDefaultDateTime();
    month = convertMonth(dateArr[1]);
    day = stoi(dateArr[2]);
    year = stoi(dateArr[4]);
}

Date::Date(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
}

void Date::setDate(int m, int d, int y) { month = m; day = d; year = y; }
int* Date::getDate() { return dateInts; }

void Date::setDefaultDateTime() { 
    // Stores current time (in seconds) since Jan 1, 1970
    std::time_t seconds = std::time(nullptr);
    // Converts the seconds to a readable format
    std::string formattedTime = std::ctime(&seconds);

    short count = 0; 
    char iterator = '\040'; 
    char nullTerm = '\0';
    
    std::string tempStr = "";

    // Splits formattedTime string into array of strings
    for (uint i = 0; i < formattedTime.length()+1; i++) {
        char c = formattedTime[i];
        if (c == iterator || c == nullTerm) {
            // Adds each piece of the split string to the arr
            dateArr[count++] = tempStr;
            tempStr = "";
        } else tempStr += c;
    }

    // Gets last two digits off the year
    std::string year = "";
    year += dateArr[4][2];
    year += dateArr[4][3];
    dateArr[4] = year;
}

short Date::convertMonth(std::string m) {
    short date = 0;
    for (short i = 0; i < short(m.length()); i++)
        date += short(m.at(i));

    short month = 0;
    switch (date) {
        // Numerical Value of each month's chars
        case 281: month = 1; break;     // Jan
        case 269: month = 2; break;     // Feb 
        case 288: month = 3; break;     // Mar
        case 291: month = 4; break;     // Apr
        case 295: month = 5; break;     // May
        case 301: month = 6; break;     // Jun
        case 299: month = 7; break;     // Jul
        case 285: month = 8; break;     // Aug
        case 296: month = 9; break;     // Sep
        case 294: month = 10; break;    // Oct
        case 307: month = 11; break;    // Nov  
        case 268: month = 12; break;    // Dec
        default:
        break;
    }
    if (month < 1) 
        std::cout << BRT <<"Invalid Month Entered" << std::endl;

    return month;
}

std::string Date::getDateString() {
    std::string m = std::to_string(month);
    std::string d = std::to_string(day);
    std::string y = std::to_string(year);
    
    return ( m + '/' + d + '/' + y );
}

void Date::printDate() {
    std::cout << getDateString();
}

void Date::componentUnitTest() {
    Date test;
    test.setDate(3, 31, 1994);
    (test.getDateString() == "3/31/1994") 
        ? std::cout << PASSED : std::cout << FAILED;
}

void Date::passedTest() { std::cout << PASSED + RTF; }
void Date::failedTest() { std::cout << FAILED + RTF; }
void Date::testComponent(std::string condition, std::string expectedResult) {
    (condition == expectedResult) ? passedTest() : failedTest(); 
}

/******************************************************************************
 * Program Class 
******************************************************************************/
class Program {
private:
    std::string name, author, dueDate, currentDate;
    int greetingFields = 4;

    std::string greetingData[4][4] = {
        { "Welcome to", "Author:", "Due Date:", "Current Date:" },
        { name, author, dueDate, currentDate }
    };

    static const std::string 
        RTF, RCF, LCF;

public:
    Program();
    Program(std::string n, std::string a, std::string d, std::string cd);

    void setName(std::string n);
    std::string getName();

    void setAuthor(std::string a);
    std::string getAuthor();

    void setDueDate(std::string d);
    std::string getDueDate();

    void setGreetingFields();

    void printGreeting();
};

const std::string Program::RTF = "\033[0m";
const std::string Program::RCF = "\033[1;97m";
const std::string Program::LCF = "\033[1;31m";

Program::Program() {
    name = "Program Name";
    author = "Author Name";
    dueDate = "Due Date";
    currentDate = "Current Date";
 }

Program::Program(std::string n, std::string a, std::string dd, std::string cd) {
    name = n;
    author = a;
    dueDate = dd;
    currentDate = cd;
    this->setGreetingFields();
}

void Program::setName(std::string n) { name = n; }
std::string Program::getName() { return name; }

void Program::setAuthor(std::string a) { author = a; }
std::string Program::getAuthor() { return author; }

void Program::setDueDate(std::string d) { dueDate = d; }
std::string Program::getDueDate() { return dueDate; }

void Program::setGreetingFields() {
    greetingData[1][0] = name;
    greetingData[1][1] = author;
    greetingData[1][2] = dueDate;
    greetingData[1][3] = currentDate;
}

void Program::printGreeting() {
    // Main greeting message
    std::string greetingMessage = LCF + greetingData[0][0] + ' ' + RCF + name + '\n';

    //  Stores length of longest field for spacing in menu
    size_t longestField = 0;

    // Finds longest string in GREETING_DATA 2D array
    for (int i = 1; i < greetingFields; i++)
        if (greetingData[0][i].length() > longestField) 
            longestField = greetingData[0][i].length();

    // Prints program's start up message
    std::cout << greetingMessage;
    for (int i = 1; i < greetingFields; i++)
        std::cout  
            << LCF << std::setw(longestField) << greetingData[0][i] 
            << RCF << ' ' + greetingData[1][i] << RTF
        << std::endl; 
}

/******************************************************************************
 * UnitTest Class 
******************************************************************************/
class UnitTest {
private:

/* Static Member Variables */
// Foreground Colors
// Bold Text
    static const std::string B_W;
    static const std::string B_R;
    static const std::string B_G;
    static const std::string B_BL;
    static const std::string B_BG;

// Background Colors
    static const std::string BG_BL;
    static const std::string BG_R;
    static const std::string BG_G;
    static const std::string BG_BG;

// Resets all styling attributes
    static const std::string R_T;

// Labels
    static const std::string TESTING;
    static const std::string PASSED;
    static const std::string FAILED;


/* Non-Static Member Variables */
// Formatting Symbols
    char borderChar = '|', 
        loadingChar = '\040';

    std::string 
        testTextColor = B_W,
        passedTextColor = B_BG,
        passedBackgroundColor = BG_BG,
        failedTextColor = B_R,
        failedBackgroundColor = B_R;

// Fomatting sizing
    size_t padding,
        screenSize;
    
// Keeps track of number of component 
// tests have been processed
    size_t testCount;

public:

    UnitTest();
    UnitTest(bool test);
    
    void setScreensize(size_t ss);
    size_t getScreensize();

    void setPadding(size_t p);
    size_t getPadding();

    void setTestCount(size_t count);
    size_t getTestCount();

    void componentUnitTest();
    template<typename T>
    bool testComponent(const T test, const T expected, const std::string testDesc = "Add test description here.");
};

const std::string 
// Foreground Colors
// Bold Text
    UnitTest::B_W = "\033[1;97m",   // Bold White
    UnitTest::B_R = "\033[1;31m",   // Bold Red
    UnitTest::B_G = "\033[1;32m",   // Bold Green
    UnitTest::B_BL = "\033[1;30m",  // Bold Black
    UnitTest::B_BG = "\033[1;92m",  // Bold Bright Green

// Background Colors
    UnitTest::BG_BL = "\033[0;40m", // Black BG
    UnitTest::BG_R = "\033[0;41m",  // Red BG
    UnitTest::BG_G = "\033[0;42m",  // Green BG
    UnitTest::BG_BG = "\033[0;102m",// Bright Green BG

// Resets all styling attributes
    UnitTest::R_T = "\033[0m",

// Labels
    UnitTest::TESTING = "Testing:",
    UnitTest::PASSED = "Passed",
    UnitTest::FAILED = "Failed";

UnitTest::UnitTest() { 
    screenSize = 50;
    padding = 1;
    testCount = 0;
    if (!testCount) 
        std::cout << '\n' << B_W << TESTING << R_T << '\n';
}

UnitTest::UnitTest(bool test) { 
    screenSize = 50;
    padding = 1;
    testCount = 0;
    if (!testCount) 
        std::cout << '\n' << B_W << TESTING << R_T << '\n';

    if (test) 
        this->componentUnitTest();
}

void UnitTest::setScreensize(size_t ss) { UnitTest::screenSize = ss; }
size_t UnitTest::getScreensize() { return UnitTest::screenSize; }

void UnitTest::setPadding(size_t p) { padding = p; }
size_t UnitTest::getPadding() { return padding; }

void UnitTest::setTestCount(size_t count) { testCount = count; }
size_t UnitTest::getTestCount() { return testCount; }

/****************************************************************************************
 * const std::string test => value to be tested
 * const std::string expected => expected result
 ***************************************************************************************/
template<typename T>
bool UnitTest::testComponent(const T test, const T expected, std::string testDesc) {
    testCount++;

    int perimeterPadding = (this->padding * 2) + 2;

    bool result = (test == expected);
    std::string status = result ? PASSED : FAILED;
    std::string INPUT = "\nInput:";
    std::string OUTPUT = "Output:";

    // Text Lengths for each line of output
    size_t lineOneTextLen = status.length() + TESTING.length();

    // Sets status color
    std::string statusTextColor = result ?  B_BG : B_R;
    std::string statusBGColor = result ?  BG_BG : BG_R;

    // Length of all o
    int loadingLength = this->screenSize - perimeterPadding - lineOneTextLen;

    std::cout << B_W << "Test #" << std::to_string(testCount) << statusTextColor << borderChar;
    for (size_t i = 0; i < this->padding; i++) 
        std::cout << R_T << loadingChar;

    std::cout << statusBGColor;
    for (int i = 0; i < loadingLength; i++)
         std::cout << loadingChar;

    for (size_t i = 0; i < this->padding; i++) 
        std::cout << R_T << loadingChar;

    std::cout 
        << statusTextColor << borderChar << status
        << INPUT << loadingChar << expected << '\040' << borderChar << '\040'
        << OUTPUT << loadingChar << test << B_W << '\n';
        
        // Checks if testDesc is longer than the screen size
        if (testDesc.length() > screenSize) {

            // Keeps tracks of which char is being printed next
            for (size_t i = 0; i < testDesc.length()+1; i++) {
                
                // Keeps track of where the current position on the screen is
                for (size_t j = 1; j < screenSize; j++) std::cout << testDesc[i++];
                
                // New line after the screensize width is met
                std::cout << '\n';

                // Checks if the first char of the next line is 
                // a blank char if so moves to next char to avoid
                // blank chars in the first space of each line
                if (testDesc[i+1] == '\040') i++;
            
            }
            std::cout << std::endl;
        // if the length of the description is less than one line the testDesc is printed in full
        } else std::cout << testDesc << '\n';

    for (size_t i = 1; i < screenSize; i++) std::cout << ('-'); 
    std::cout << R_T << std::endl;
        
    return result;
}

// Testing Entry Point
void UnitTest::componentUnitTest() { 
    
    std::string testValueStr;
    int testValueNum;

    testValueStr = "tyler";
    testComponent<std::string>(testValueStr, "tyler");

    char testValueChar = 'c';
    testComponent<char>(testValueChar, 'c');

    testValueNum = 50;
    testComponent<size_t>(getScreensize(), testValueNum);

    testValueStr = "50";
    testComponent<std::string>(std::to_string(getScreensize()), testValueStr);

}

/******************************************************************************
 * Global Constants 
******************************************************************************/

/* Testing Config */
// Enables testing mode
const bool TEST_MODE = false;
// Enables Strict Test Mode
const bool STRICT_TEST_MODE = false;

/* Program Instantiation Config */
const std::string PROGRAM_NAME = "Hokeemon";
const std::string PROGRAM_AUTHOR = "Tyler Swindell";
Date dueDate(4,26,22);
const std::string PROGRAM_DUE_DATE = dueDate.getDateString();
Date currentDate;
const std::string PROGRAM_CURRENT_DATE = currentDate.getDateString();

const std::string   
	TR = "\033[0m",
	BRT = "\033[1;31m",
	BWT = "\033[1;97m";


// Text displayed in quitProgram option
const std::string EXIT_MESSAGE = (
	BRT + 
	"\nThank you for using " + 
	BWT +
	PROGRAM_NAME +
	BRT + 
	"!\n" + TR
);

/* Menu Config */
const char 
	LISTEN_KEY = 'L',
	PLAY_KEY = 'P',
	FEED_KEY = 'F',
	QUIT_KEY = 'Q',
	YES_KEY = 'Y',
	NO_KEY = 'N';

const std::string 
	LISTEN_PROMPT = ": Listen\n",
	PLAY_PROMPT = ": Play\n",
	FEED_PROMPT = ": Feed\n",
	QUIT_PROMPT = ": Quit Program\n",
	Y_PROMPT = ": Yes, I need to prove myself!\n",
	N_PROMPT = ": No, I can't handle this responsibility.\n",
	INVALID_ENTRY = (BRT + "Invalid Entry!" + TR);



/* 
 * 0 = UNRESPONSIVE, 
 * 1 = ALIVE,
 * 2 = STARVING, 
 * 3 = SATIATED, 
 * 4 = BORED, 
 * 5 = ENTERTAINED 
 * 6 = WITHERING
 * 7 = THRIVING
 */ 
enum Status {UNRESPONSIVE, ALIVE, STARVING, SATIATED, BORED, ENTERTAINED, WITHERING, THRIVING, EVOLVING};
/******************************************************************************
 * Creature Class
******************************************************************************/
// Specification C2 - Creature class
class Creature {
private:
	const std::string c_birthdate_ = Date().getDateString();
	const static std::string statuses[];
	const static std::string outputLabels[];

protected:
	std::string name_;

	size_t
	// Min: 0, Max: None
		hunger_;
	intmax_t
	// Min: None, Max: 20
		boredom_;

	Status status_;

	// Specification C1 - PassTime()
	virtual void passTime() = 0;
	static size_t randULong(size_t min, size_t max);

public:

	Creature();
	virtual ~Creature();

	// Specification C4 - Overload «
	friend std::ostream& operator<<(std::ostream& stream, Creature& c);
	friend std::istream& operator>>(std::istream& stream, Creature& c);

	std::string setName(std::string n);
	std::string name();

	// Specification B2 - Virtual Class Creature
	virtual Status setStatus() = 0;
	virtual void listen() = 0;
	virtual void play() = 0;
	virtual void feed() = 0;

	void setHunger(size_t h);
	size_t hunger();
	
	void setBoredom(intmax_t b);
	intmax_t boredom();

	void setStatus(Status s);
	Status status();
	std::string statusString();

};

const std::string Creature::statuses[] = {"Unresponsive", "Alive", "Starving", "Satiated", "Bored", "Entertained", "Withering", "Thriving", "Evolving"};
const std::string Creature::outputLabels[] = {"Name", "Hunger", "Boredom", "Status", "Born"};

size_t Creature::randULong(size_t min, size_t max) { return ((rand() % max) + min); }

Creature::Creature() { }
Creature::~Creature() { }


std::ostream& operator<<(std::ostream& stream, Creature& c) {
	return ( stream
		<< "Name: "     << c.name_                  << " | "
		<< "Hunger: "   << c.hunger_                << " | "
		<< "Boredom: "  << c.boredom_               << " | "
		<< "Status: "   << c.statuses[c.status_]    << " | "
		<< "Born: "     << c.c_birthdate_
	);
}

// Specification A1 - Critter Name
std::istream& operator>>(std::istream& stream, Creature& c) {
	std::cout << "Rename your creature: ";
	std::string n;
	stream >> n;
	c.setName(n);
	return (stream);
}

	std::string Creature::setName(std::string n) { return (name_ = n); }
	std::string Creature::name() { return name_; }

	void Creature::setHunger(size_t h) { hunger_ = h;}
	size_t Creature::hunger() { return hunger_;}

	void Creature::setBoredom(intmax_t b) { boredom_ = b;}
	intmax_t Creature::boredom() { return boredom_;}
	
	void Creature::setStatus(Status s) { status_ = s;}
	Status Creature::status() { return status_; }
	std::string Creature::statusString() { return statuses[status_]; }

/******************************************************************************
 * Hokeemon Class
******************************************************************************/
// Specification B1 - Child Class
class Hokeemon : public Creature {
protected:
	void passTime();
	static const std::string c_species_;

public:
	Hokeemon(std::string n = "Hokee", size_t min = 0, size_t max = 5);
	~Hokeemon();

	Hokeemon(const Hokeemon &h);
	
	//Specification B3 - Overload Assignment Operator
	Hokeemon operator=(const Hokeemon& right);

	//Specification B4 - Overload + Operator
	friend Hokeemon operator+(const Hokeemon& a, const Hokeemon& b);
	
	Status setStatus();
	void listen();
	void play();
	void feed();

};

const std::string Hokeemon::c_species_ = "Hokeemon";

Hokeemon::Hokeemon(std::string n, size_t min, size_t max) {
	name_ = n;
	hunger_ = randULong(min+1, max);
	boredom_ = randULong(min, max);
	setStatus();
}

Hokeemon::~Hokeemon() { }

// Specification A2 - Copy Constructor
// This constructor would create clones of a currently existing Hokeemon
Hokeemon::Hokeemon(const Hokeemon &h) {
	name_ = h.name_ + "\'s Clone";
	hunger_ = h.hunger_;
	boredom_ = h.boredom_;
	status_ = h.status_;
}

//Specification B3 - Overload Assignment Operator
Hokeemon Hokeemon::operator=(const Hokeemon& right) {
	if (this != &right) {
		this->name_ = right.name_;
		this->hunger_ = right.hunger_;
		this->boredom_ = right.boredom_;
		this->status_ = right.status_;
	}

	return *this;
}

//Specification B4 - Overload + Operator
Hokeemon operator+(Hokeemon& a, Hokeemon& b) {
	Hokeemon r;
	std::string 
		nameA = a.name().substr(0, a.name().length()/2),
		nameB = b.name().substr(
			b.name().length()/2, b.name().length()
		);
	r.setName(nameA + nameB);
	r.setBoredom(a.boredom() + b.boredom());
	r.setHunger(a.hunger() + b.hunger());
	return r;
}

/* Manages status_ based on hunger_ and boredom_ values */
Status Hokeemon::setStatus() {
	
	// If hunger_ reaches 0 or boredom_ exceeds 20 the Hokeemon becomes UNRESPONSIVE
	if (!hunger_ || boredom_ > 20) return UNRESPONSIVE;

	// If hunger_ reaches 20 and boredom_ drops to 0 the Hokeemon begins THRIVING
	// If only hunger_ reaches 20 the Hokemon becomes SATIATED
	// If only boredom_ drops to 0 the Hokemon becomes ENTERTAINED
	if (hunger_  >= 20 || boredom_ <= 0) {
		if (hunger_ >= 20 && boredom_ <= 0) status_ = THRIVING; 
		else (hunger_ >= 20) ? status_ = SATIATED : status_ = ENTERTAINED;
	}

	// If hunger_ falls to 5 and boredom_ reaches to 15 the Hokeemon begins WITHERING
	// If only hunger_ falls to 5 the Hokemon becomes STARVING
	// If only boredom_ drops to 15 the Hokemon becomes BORED
	if (hunger_ <= 5 || boredom_ >= 15) {
		if (hunger_ <= 5 && boredom_ >= 15) status_ = WITHERING; 
		else (hunger_ <= 5) ? status_ = STARVING : status_ = BORED;
	}
	
	return status_;
}

void Hokeemon::passTime() {
	hunger_--;
	boredom_++;
	status_ = setStatus();
}

void Hokeemon::listen() {
	std::cout << *this;
	passTime();
}

void Hokeemon::play() {
	std::cout << "You play with " << name_ << ".\nThey are less bored now!\n";
	boredom_ -= randULong(4, 8);
	passTime();
}

void Hokeemon::feed() {
	std::cout << "You feed " << name_ << ".\nThey are less hungry now!\n";
	hunger_ += randULong(3, 6);
	passTime();
}

// Specification A3 - Second Child Class
class BabyHokeemon: public Creature
{
protected:
	void passTime();
public:
	BabyHokeemon(std::string n, size_t min = 0, size_t max = 5);
	BabyHokeemon(const BabyHokeemon &h);
	~BabyHokeemon();


	Status setStatus();
	void listen();
	void play();
	void feed();
};

BabyHokeemon::BabyHokeemon(std::string n, size_t min, size_t max) {
	name_ = "Baby " + n;
	hunger_ = randULong(min+1, max);
	boredom_ = randULong(min, max);
	setStatus();
}

// Specification A2 - Copy Constructor
// This constructor would create clones of a currently existing Hokeemon
BabyHokeemon::BabyHokeemon(const BabyHokeemon &h) {
	name_ = h.name_ + "\'s Clone";
	hunger_ = h.hunger_;
	boredom_ = h.boredom_;
	status_ = h.status_;
}

BabyHokeemon::~BabyHokeemon() { }

/* Manages status_ based on hunger_ and boredom_ values */
Status BabyHokeemon::setStatus() {
	
	// If hunger_ reaches 0 or boredom_ exceeds 20 the Hokeemon becomes UNRESPONSIVE
	if (!hunger_ || boredom_ > 20) return UNRESPONSIVE;

	// If hunger_ reaches 12 and boredom_ drops to 6 the Hokeemon begins THRIVING
	// If only hunger_ reaches 12 the Hokemon becomes SATIATED
	// If only boredom_ drops to 6 the Hokemon becomes ENTERTAINED
	if (hunger_  >= 12 || boredom_ <= 6) {
		if (hunger_ >= 12 && boredom_ <= 6) status_ = THRIVING; 
		// if (hunger_ >= 20 && boredom_ <= 0) status_ = EVOLVING; 
		else (hunger_ >= 12) ? status_ = SATIATED : status_ = ENTERTAINED;

	}

	// If hunger_ falls to 2 and boredom_ reaches to 18 the Hokeemon begins WITHERING
	// If only hunger_ falls to 2 the Hokemon becomes STARVING
	// If only boredom_ drops to 18 the Hokemon becomes BORED
	if (hunger_ <= 2 || boredom_ >= 18) {
		if (hunger_ <= 2 && boredom_ >= 18) status_ = WITHERING; 
		else (hunger_ <= 2) ? status_ = STARVING : status_ = BORED;
	}
	
	return status_;
}

void BabyHokeemon::passTime() {
	hunger_--;
	boredom_++;
	status_ = setStatus();
}

void BabyHokeemon::listen() {
	std::cout << *this;
	passTime();
}

void BabyHokeemon::play() {
	std::cout << "You play with " << name_ << ".\nThey are less bored now!\n";
	boredom_ -= randULong(1, 4);
	passTime();
}

void BabyHokeemon::feed() {
	std::cout << "You feed " << name_ << ".\nThey are less hungry now!\n";
	hunger_ += randULong(2, 3);
	passTime();
}


/******************************************************************************
 * Function Prototypes
******************************************************************************/

/* Control Functions */
void unitTest();
void mainLoop();

template <typename T>
bool menuInput(T &c);
bool quitProgram();

/* Output Functions */
void printMenu();
void printReplayMenu();
template <typename T>
void statusTextSwitch(T &c);
void newLine(size_t count = 1);
void textReset();

template<typename T>
void print(T msg, bool endLine = false, size_t count = 1); 


/* Input Functions */
char getCharInput(const std::string &prompt = "-1", bool caseSensetive = false);
std::string getStringInput(const std::string &prompt = "-1");
void clearCinBuffer();

/* Processing Functions */
template <typename T>
bool statusOfHokee(T &c);
bool isValidChoice(const char &choice);
template <typename T>
size_t getSizeOfArray(const T &arr);
void setRand();
void forEach(Vector<Hokeemon> vec, void (*func)(Hokeemon));

void errorSwitch(int err);


int main() {
	// Program config class
	Program app(PROGRAM_NAME, PROGRAM_AUTHOR, PROGRAM_DUE_DATE, PROGRAM_CURRENT_DATE);

	app.printGreeting();

	if (TEST_MODE || STRICT_TEST_MODE) unitTest();

	if (!STRICT_TEST_MODE) mainLoop();
	return 0;
}

/******************************************************************************
 * Control Functions
******************************************************************************/
void unitTest() {
	UnitTest ut;
	// Bools will dictate which tests trigger
	bool 
		hokeeTest = false,
		destructor = false,
		babyTest = true;

	// Array of all test bools
	bool tests[] = { 
		/* hokeeTest,
		destructor */
		babyTest
	};

	// Initiates Strict Test Mode
	if (STRICT_TEST_MODE) 
		for (size_t i = 0; i++ < getSizeOfArray(tests);)
			tests[i] = true;

	if (babyTest) {
		BabyHokeemon* h = new BabyHokeemon("Juju");
		print(h->name(), true);
		delete h;
	}


	if (destructor) {
		Hokeemon* h = new Hokeemon("Juju");
		print(h->name(), true);
		delete h;
	}

	if (hokeeTest) {
		Hokeemon* h1 = new Hokeemon("Jim");

		std::string testStr = h1->name();
		std::string expctStr = "Jim";
		std::string testDesc = "Name input / output.";
		ut.testComponent(testStr, expctStr, testDesc);

		h1->setHunger(5);
		size_t testSh = h1->hunger();
		size_t expctSh = 5;
		testDesc = "Hunger input / output.";
		ut.testComponent(testSh, expctSh, testDesc);

		std::string testSt = h1->statusString();
		std::string expctSt = "Alive";
		testDesc = "Status input / output.";
		ut.testComponent(testSt, expctSt, testDesc);

		Hokeemon* h2 = new Hokeemon("Alec");

		Hokeemon* h3 = h1;

		h1->setName("Tyler");

		int testInt = 1;
		int expctInt = 1;
		testDesc = "This is a really long test description written to test and demonstrate screen size effecting description text width and wrapping on the screen.";
		ut.testComponent(testInt, expctInt, testDesc);

		Vector<Hokeemon> testVec;

		testVec.push(*h1);
		testVec.push(*h2);
		testVec.push(*h3);

		// Specification A4 - Write a Lambda
		forEach(testVec, [](Hokeemon val){ std::cout << val << std::endl; });
	}

	print(TR);
}

// Controls main loop of program
void mainLoop() {

	bool newHoke = true;
	bool play = true;

	do {
		setRand();
		std::string hName = getStringInput(BRT + "\nName your new Hokeemon: " + BWT);
		BabyHokeemon* h = new BabyHokeemon(hName);
		print("\nSay hello to " + h->name() + "!", true);
		std::cout << *h << std::endl;
		do {
			printMenu();
			play = newHoke = menuInput(*h);
			if (play) if (!(statusOfHokee(*h))) play = newHoke = quitProgram();
		} while(play);
		delete h;
	} while(newHoke);
}

template <typename T>
bool menuInput(T &c) {
	try {
		char choice = getCharInput((BRT + "\nEnter an option: " + BWT));

		switch(choice) {
			case LISTEN_KEY: c.listen();
				break;
			case PLAY_KEY: c.play();
				break;
			case FEED_KEY: c.feed();
				break;
			case QUIT_KEY: 
				return quitProgram();
			default: throw 1;
			break;
		}
	// Specification C3 - Validate Input
	} catch(int err) { errorSwitch(err); }

	return true;
}

template <typename T>
bool statusOfHokee(T &c) {
	bool continuePlay = true;
	bool errorThrown = false;
	newLine();

	if (c.status() == 0) {
		print("Oh no!\nYour Hokeemon has become unresponsive!", true);
		do {
			printReplayMenu();
			char choice = getCharInput((BRT + "\nEnter an option: " + BWT));
			switch(choice) {
				case YES_KEY: 
					continuePlay = true;
					errorThrown = false;
					break;

				case NO_KEY: 
					continuePlay = false;
					errorThrown = false;
					break;

				default: 
					errorThrown = true;
					errorSwitch(1); 
					break;
			}

		} while(errorThrown);
	} else { statusTextSwitch(c); }

	return continuePlay;
}

// Option triggered when `QUIT` constant is typed into menu
bool quitProgram() {
	print(EXIT_MESSAGE, true);
	return false;
}

/******************************************************************************
 * Input Functions
******************************************************************************/
char getCharInput(const std::string &prompt, bool caseSensetive) {
	if (prompt != "-1") print(prompt);

	std::string input;
	getline(std::cin, input);
	if (input.length() > 1) throw 0;
	return (caseSensetive) ? input[0] : std::toupper(input[0]);
}

std::string getStringInput(const std::string &prompt) {
	if (prompt != "-1") print(prompt);

	std::string input;
	getline(std::cin, input);
	if (input.length() > 25) throw 2;
	return input;
}

// Ignores and clears cin buffer
void clearCinBuffer() {
	std::cin.clear();
	// numeric_limits snippet from: geeksforgeeks.org/clearing-the-input-buffer-in-cc/
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
}

/******************************************************************************
 * Output Functions
******************************************************************************/
// Game menu display
void printMenu() {
	std::cout 
		<< BRT  << "\nMain Menu\n" 
		<< BRT  << LISTEN_KEY   << BWT << LISTEN_PROMPT
		<< BRT  << PLAY_KEY     << BWT << PLAY_PROMPT
		<< BRT  << FEED_KEY     << BWT << FEED_PROMPT
		<< BRT  << QUIT_KEY		<< BWT << QUIT_PROMPT
	<< TR;
}

void printReplayMenu() {
	std::cout 
		<< BRT  << "\nWould you like a new Hokeemon?\n" 
		<<	BRT	<< YES_KEY	<<	BWT	<<	Y_PROMPT
		<<	BRT	<< NO_KEY	<<	BWT	<<	N_PROMPT
	<< TR;
}

template <typename T>
void statusTextSwitch(T &c) {
	switch(c.status()) {
		case 1: // ALIVE
			print(c.name() + "'s alive and well.");
			break;
		case 2: // STARVING
			print(c.name() + "'s starving!\nMake sure you're feeding them!");
			break;
		case 3: // SATIATED
			print(c.name() + "'s stuffed. They couldn't eat another bite.");
			break;
		case 4: // BORED
			print(c.name() + "'s so bored they may just slip into a coma.");
			break;
		case 5: // ENTERTAINED
			print(c.name() + "'s having an amazing time!");
			break;
		case 6: // WITHERING
			print(c.name() + " is rapidly withering away!");
			break;
		case 7: // THRIVING
			print(c.name() + " couldn't be living a better life!");
			break;
		default: 
			print(c.name() + " is experiencing something we've never seen before!");
			break;
	}
	newLine();
}

// Count is optional | Defaults: count = 1 
void newLine(size_t count) {
	// If count is manually set to 0 return out of function
	if (count < 1) return;

	// Will be skipped if no parameters set or user inputs 1 as param
	if (count > 1)
		for (size_t i = 1; i < count; i++) std::cout << '\n';

	// Will run a single cout
	std::cout << '\n';
}

template<typename T>
void print(T msg, bool endLine, size_t count) {
	std::cout << msg;
	if (endLine) newLine(count);
}

// Function which resets text formatting
void textReset() { print(TR); }

/******************************************************************************
 * Processing Functions
******************************************************************************/
template <typename T>
size_t getSizeOfArray(const T &arr) { return sizeof(arr)/sizeof(arr[0]); }

void setRand() { srand(time(0)); }

void forEach(Vector<Hokeemon> vec, void (*func)(Hokeemon h)) {
	for (size_t i = 0; i < vec.size(); i++) func(vec.get(i));
}

void errorSwitch(int err) {
	switch(err) {
		case 0: print(BRT + "\nInput only one character to continue.", true);
			break;
		case 1: print('\n'+INVALID_ENTRY, true);
			break;
		case 2: print(BRT + "\nName must be less than 25 characters long.", true);
			break;
		default: print("An unexpected error has occurred.");
			break;
	}
	print(TR);
}
