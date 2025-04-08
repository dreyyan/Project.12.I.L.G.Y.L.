// FINANCIAL STATISTICS:
// Tracks the financial performance of the player's business
struct FinancialStats {
    double money;           // Current cash available
    double revenue;         // Total income before expenses
    double expenses;        // Cost of operation
    double profit;          // Total income /wo expenses
    double debt;            // Money borrowed
};

// PERSONAL STATISTICS:
// Tracks the player's mental & emotional state, influencing decisions & performance
struct PersonalStats {
    double happiness;       // Player's happiness level
    double stress;          // Player's stress level
    double motivation;      // Player's motivation level
};

// BUSINESS STATISTICS:
// Reflects the player's business operations & growth
struct BusinessStats {
    int level;              // Current level of business
    int employees;          // Total # of employees
    int popularity;         // Customer popularity/satisfaction
};

// GAME STATISTICS:
// Tracks the player's game achievements & progression
struct GameStats {
    int productsSold;       // Total # of products sold
    int storyProgression;   // Percent(%) progression of the game's story
    double totalProfit;     // Total profit earned by the business
};

class Portfolio {
    FinancialStats financial_statistics;
    PersonalStats personal_statistics;
    BusinessStats business_statistics;
    GameStats game_statistics;

public:
    // Default Constructor
    Portfolio() {}
    // Parameterized Constructor
    Portfolio(FinancialStats fs, PersonalStats ps, BusinessStats bs, GameStats gs)
    : financial_statistics(fs), personal_statistics(ps), business_statistics(bs), game_statistics(gs) {}
};