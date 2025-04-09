// PLAYER STATISTICS:
// Saves the player's data
struct PlayerData {
    string characterName;       // Name of the created character
    string standName;           // Name of the Lemonade stand
    int level;                  // Current level of the player
    int currentChapter;         // Current chapter of the story
    string saveTimestamp;       // Timestamp of the latest save
    int playtimeDuration;       // Duration of gameplay in "HH-MM" format
};

// FINANCIAL STATISTICS:
// Tracks the financial performance of the player's business
struct FinancialStats {
    double money;               // Current cash available
    double revenue;             // Total income before expenses
    double expenses;            // Cost of operation
    double debt;                // Money borrowed
};

// PERSONAL STATISTICS:
// Tracks the player's mental & emotional state, influencing decisions & performance
struct PersonalStats {
    double happiness;           // Player's happiness level
    double stress;              // Player's stress level
    double motivation;          // Player's motivation level
};

// BUSINESS STATISTICS:
// Reflects the player's business operations & growth
struct BusinessStats {
    int employees;              // Total # of employees
    int popularity;             // Customer popularity/satisfaction
    int recipesOwned;           // # of recipes owned
};

// GAME STATISTICS:
// Tracks the player's game achievements & progression
struct GameStats {
    int productsSold;           // Total # of products sold
    double totalProfit;         // Total profit earned by the business
    double highestDailyProfit;  // Highest profit in a day
};

struct SaveData {
    PlayerData player_data;
    FinancialStats financial_statistics;
    PersonalStats personal_statistics;
    BusinessStats business_statistics;
    GameStats game_statistics;
};