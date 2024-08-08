#include <iostream>
#include <mariadb/conncpp.hpp>
#include <string>
#include <vector>
class DB
{
private:
    std::string mID;                // DB 접속 아이디
    std::string mPW;                // DB 접속 패스워드
    sql::Connection* mConnection;   // DB 연결
    
public:
    DB() { }
    void setAccount(const std::string& id, const std::string& pw)   // DB 아이디 비밀번호 설정
    {
        mID = id;
        mPW = pw;
    }
    sql::ResultSet* executeQuery(const std::string& query)  // 쿼리문을 입력받아 res를 리턴
    {
        sql::Statement* stmnt(mConnection->createStatement());
        sql::ResultSet* res = stmnt->executeQuery(query);
        return res;
    }
    void connect()     // db와 연결
    {
        try
        {
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            sql::SQLString url = "jdbc:mariadb://10.10.21.117:3306/PROJECT";    // db의 주소
            sql::Properties properties({{"user", mID}, {"password", mPW}});     // 로그인
            mConnection = driver->connect(url, properties);
            std::cout << "DB 접속 성공\n";
        }
        catch(sql::SQLException& e)
        {
            std::cerr << "DB 접속 실패: " << e.what() << std::endl;
            exit(1);
        }
    }
    ~DB() { }
};

class Region
{
private:
    DB& mDB;
public:
    Region(DB& db) : mDB(db) {}
    void maxCrime(const std::string& region)
    {
        try
        {
            std::string query = "SELECT 범죄대분류, 범죄중분류," + region + " FROM CRIME_REGION ORDER BY 서울 DESC LIMIT 1;";
            sql::ResultSet *res = mDB.executeQuery(query);
            while (res->next())
            {
                std::cout << "지역 = " << region;
                std::cout << " / 최대범죄 / 범죄대분류 = " << res->getString(1);
                std::cout << ", 범죄중분류 = " << res->getString(2);
                std::cout << ", 횟수 = " << res->getInt(3);
                std::cout << std::endl;
            }
        }
        catch(sql::SQLException& e)
        {
            std::cerr << "입력에러: " << e.what() << std::endl;
        }
    }
    void minCrime(const std::string& region)
    {
        try
        {
        std::string query = "SELECT 범죄대분류, 범죄중분류," + region + " FROM CRIME_REGION ORDER BY 서울 LIMIT 1;";
        sql::ResultSet *res = mDB.executeQuery(query);
        while (res->next()) {
            std::cout << "지역 = " << region;
            std::cout << " / 최소범죄 / 범죄대분류 = " << res->getString(1);
            std::cout << ", 범죄중분류 = " << res->getString(2);
            std::cout << ", 횟수 = " << res->getInt(3);
            std::cout << std::endl;
        }
        }
        catch(sql::SQLException& e)
        {
            std::cerr << "입력에러: " << e.what() << std::endl;
        }
    }
    void showColumn()
    {
        try
        {
            int i = 0;
            std::string query = "SHOW COLUMNS FROM CRIME_REGION;";
            sql::ResultSet *res = mDB.executeQuery(query);
            while (res->next()) {
                i++;
                if (i > 2)
                {
                    std:: cout << i-2 << ". ";
                    std::cout << res->getString(1);
                    std::cout << std::endl;
                }
            }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
        }
    }
};

class Place
{
    private:
        DB& mDB;
    public:
        Place(DB& db) : mDB(db) {}
        void maxCrime(const std::string& place)
        {
            try
            {
                std::string query = "SELECT 범죄대분류, 범죄중분류," + place + " FROM CRIME_PLACE ORDER BY 연립다세대 DESC LIMIT 1;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next())
                {
                    std::cout << "장소 = " << place;
                    std::cout << " / 최대범죄 / 범죄대분류 = " << res->getString(1);
                    std::cout << ", 범죄중분류 = " << res->getString(2);
                    std::cout << ", 횟수 = " << res->getInt(3);
                    std::cout << std::endl;
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void minCrime(const std::string& place)
        {
            try
            {
                std::string query = "SELECT 범죄대분류, 범죄중분류," + place + " FROM CRIME_PLACE ORDER BY 연립다세대 LIMIT 1;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next())
                {
                    std::cout << "장소 = " << place;
                    std::cout << " / 최소범죄 / 범죄대분류 = " << res->getString(1);
                    std::cout << ", 범죄중분류 = " << res->getString(2);
                    std::cout << ", 횟수 = " << res->getInt(3);
                    std::cout << std::endl;
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showColumn()
        {
            try
            {
                int i = 0;
                std::string query = "SHOW COLUMNS FROM CRIME_PLACE;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        std:: cout << i-2 << ". ";
                        std::cout << res->getString(1);
                        std::cout << std::endl;
                    }
                }
                }
                catch(sql::SQLException& e)
                {
                    std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
};

class TimeWeek
{
    private:
        DB& mDB;
    public:
        TimeWeek(DB& db) : mDB(db) {}
        void maxCrime(const std::string& time)
        {
            try
            {
                std::string query = "SELECT 범죄대분류, 범죄중분류," + time + " FROM CRIME_TIME_WEEK ORDER BY TIME_03 DESC LIMIT 1;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next())
                {
                    std::cout << "시간 or 요일 = " << time;
                    std::cout << " / 최대범죄 / 범죄대분류 = " << res->getString(1);
                    std::cout << ", 범죄중분류 = " << res->getString(2);
                    std::cout << ", 횟수 = " << res->getInt(3);
                    std::cout << std::endl;
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void minCrime(const std::string& time)
        {
            try
            {
                std::string query = "SELECT 범죄대분류, 범죄중분류," + time + " FROM CRIME_TIME_WEEK ORDER BY TIME_03 LIMIT 1;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next())
                {
                    std::cout << "시간 or 요일 = " << time;
                    std::cout << " / 최소범죄 / 범죄대분류 = " << res->getString(1);
                    std::cout << ", 범죄중분류 = " << res->getString(2);
                    std::cout << ", 횟수 = " << res->getInt(3);
                    std::cout << std::endl;
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showColumn()
        {
            try
            {
                int i = 0;
                std::string query = "SHOW COLUMNS FROM CRIME_TIME_WEEK;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        std:: cout << i-2 << ". ";
                        std::cout << res->getString(1);
                        std::cout << std::endl;
                    }
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
};

class AgeGender
{
    private:
        DB& mDB;
    public:
        AgeGender(DB& db) : mDB(db) {}
        void maxCrime(const std::string& ages)
        {
            try
            {
                std::string query = "SELECT 범죄대분류, 범죄중분류," + ages + " FROM CRIME_AGE_SEX ORDER BY 남자20세이하 DESC LIMIT 1;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next())
                {
                    std::cout << "찾고자 하는 대상 = " << ages;
                    std::cout << " / 최대범죄 / 범죄대분류 = " << res->getString(1);
                    std::cout << ", 범죄중분류 = " << res->getString(2);
                    std::cout << ", 횟수 = " << res->getInt(3);
                    std::cout << std::endl;
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void minCrime(const std::string& ages)
        {
            try
            {
                std::string query = "SELECT 범죄대분류, 범죄중분류," + ages + " FROM CRIME_AGE_SEX ORDER BY 남자20세이하 LIMIT 1;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next())
                {
                    std::cout << "찾고자 하는 대상 = " << ages;
                    std::cout << " / 최소범죄 / 범죄대분류 = " << res->getString(1);
                    std::cout << ", 범죄중분류 = " << res->getString(2);
                    std::cout << ", 횟수 = " << res->getInt(3);
                    std::cout << std::endl;
                }
            }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showColumn()
        {
            try
            {
                int i = 0;
                std::string query = "SHOW COLUMNS FROM CRIME_AGE_SEX;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        std:: cout << i-2 << ". ";
                        std::cout << res->getString(1);
                        std::cout << std::endl;
                    }
                }
                }
                catch(sql::SQLException& e)
                {
                    std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
};

class Crime
{
    private:
        DB& mDB;
    public:
        Crime(DB& db) : mDB(db) { }
        void showColumn()
        {
            try
            {
                std::string query = "SELECT 범죄중분류 FROM CRIME_AGE_SEX;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    std::cout << res->getString(1);
                    std::cout << std::endl;
                }
                }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showMaxMin_Age(const std::string& crime)
        {
            try
            { 
                int i = 0;
                int j = 0;
                int max;
                int min;
                int maxI;
                int minI;
                std::string aa[20];
                std::string b;
                std::string query = "SHOW COLUMNS FROM CRIME_AGE_SEX;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        b = res->getString(1);
                        aa[j++] = b;
                    }
                }
                std::string query1 = "SELECT * FROM CRIME_AGE_SEX WHERE 범죄중분류 = '" + crime + "';";
                sql::ResultSet *res1 = mDB.executeQuery(query1);
                while (res1->next())
                {
                    max = res1->getInt(3); 
                    min = res1->getInt(3);
                    maxI = 3;
                    minI = 3;
                    for (int i = 4; i < 15; i++)
                    {
                        maxI = (max < res1->getInt(i)) ? i : maxI;
                        max = (max < res1->getInt(i)) ? res1->getInt(i) : max;
                        minI = (min > res1->getInt(i)) ? i : minI;
                        min = (min > res1->getInt(i)) ? res1->getInt(i) : min;
                    }     
                    std::cout << "분류: 나이와 성별" << std::endl;
                    std::cout << "최대: " << aa[maxI-3] << ": " << "  " << max << " | ";
                    std::cout << "최소: " << aa[minI-3] << ": " << "  " << min << std::endl;
                }
                }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showMaxMin_Pla(const std::string& crime)
        {
            try
            { 
                int i = 0;
                int j = 0;
                int max;
                int min;
                int maxI;
                int minI;
                std::string aa[36];
                std::string b;
                std::string query = "SHOW COLUMNS FROM CRIME_PLACE;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        b = res->getString(1);
                        aa[j++] = b;
                    }
                }
                std::string query1 = "SELECT * FROM CRIME_PLACE WHERE 범죄중분류 = '" + crime + "';";
                sql::ResultSet *res1 = mDB.executeQuery(query1);
                while (res1->next())
                {
                    max = res1->getInt(3); 
                    min = res1->getInt(3);
                    maxI = 3;
                    minI = 3;
                    for (int i = 4; i < 36; i++)
                    {
                        maxI = (max < res1->getInt(i)) ? i : maxI;
                        max = (max < res1->getInt(i)) ? res1->getInt(i) : max;
                        minI = (min > res1->getInt(i)) ? i : minI;
                        min = (min > res1->getInt(i)) ? res1->getInt(i) : min;
                    }     
                    std::cout << "분류: 장소" << std::endl;
                    std::cout << "최대: " << aa[maxI-3] << ": " << "  " << max << " | ";
                    std::cout << "최소: " << aa[minI-3] << ": " << "  " << min << std::endl;
                }
                }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showMaxMin_Reg(const std::string& crime)
        {
            try
            { 
                int i = 0;
                int j = 0;
                int max;
                int min;
                int maxI;
                int minI;
                std::string aa[22];
                std::string b;
                std::string query = "SHOW COLUMNS FROM CRIME_REGION;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        b = res->getString(1);
                        aa[j++] = b;
                    }
                }
                std::string query1 = "SELECT * FROM CRIME_REGION WHERE 범죄중분류 = '" + crime + "';";
                sql::ResultSet *res1 = mDB.executeQuery(query1);
                while (res1->next())
                {
                    max = res1->getInt(3); 
                    min = res1->getInt(3);
                    maxI = 3;
                    minI = 3;
                    for (int i = 4; i < 22; i++)
                    {
                        maxI = (max < res1->getInt(i)) ? i : maxI;
                        max = (max < res1->getInt(i)) ? res1->getInt(i) : max;
                        minI = (min > res1->getInt(i)) ? i : minI;
                        min = (min > res1->getInt(i)) ? res1->getInt(i) : min;
                    }     
                    std::cout << "분류: 지역" << std::endl;
                    std::cout << "최대: " << aa[maxI-3] << ": " << "  " << max << " | ";
                    std::cout << "최소: " << aa[minI-3] << ": " << "  " << min << std::endl;
                }
                }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showMaxMin_Tim(const std::string& crime)
        {
            try
            { 
                int i = 0;
                int j = 0;
                int max;
                int min;
                int maxI;
                int minI;
                std::string aa[22];
                std::string b;
                std::string query = "SHOW COLUMNS FROM CRIME_TIME_WEEK;";
                sql::ResultSet *res = mDB.executeQuery(query);
                while (res->next()) {
                    i++;
                    if (i > 2)
                    {
                        b = res->getString(1);
                        aa[j++] = b;
                    }
                }
                std::string query1 = "SELECT * FROM CRIME_TIME_WEEK WHERE 범죄중분류 = '" + crime + "';";
                sql::ResultSet *res1 = mDB.executeQuery(query1);
                while (res1->next())
                {
                    max = res1->getInt(3); 
                    min = res1->getInt(3);
                    maxI = 3;
                    minI = 3;
                    for (int i = 4; i < 19; i++)
                    {
                        maxI = (max < res1->getInt(i)) ? i : maxI;
                        max = (max < res1->getInt(i)) ? res1->getInt(i) : max;
                        minI = (min > res1->getInt(i)) ? i : minI;
                        min = (min > res1->getInt(i)) ? res1->getInt(i) : min;
                    }     
                    std::cout << "분류: 시간" << std::endl;
                    std::cout << "최대: " << aa[maxI-3] << ": " << "  " << max << " | ";
                    std::cout << "최소: " << aa[minI-3] << ": " << "  " << min << std::endl;
                }
                }
            catch(sql::SQLException& e)
            {
                std::cerr << "입력에러: " << e.what() << std::endl;
            }
        }
        void showMaxMin_Wea(const std::string& crime)
        {
            std::cout << "분류: 날씨" << std::endl;
            std::cout << "최대: " << "맑음" <<" | ";
            std::cout << "최소: " << "맑음" << std::endl;
        }
};

class Handler
{
private:
    DB mDB;
public:
    void showRegionMaxNmin()
    {
        std::string region;
        Region rr(mDB);
        rr.showColumn();
        std::cout << "지역을 입력해라: ";
        std::cin >> region;
        rr.maxCrime(region);
        rr.minCrime(region);
    }
    void showPlaceMaxNmin()
    {
        std::string place;
        Place rr(mDB);
        rr.showColumn();
        std::cout << "장소를 입력해라: ";
        std::cin >> place;
        rr.maxCrime(place);
        rr.minCrime(place);
    }
    void showTimeWeek()
    {
        std::string tiwe;
        TimeWeek rr(mDB);
        rr.showColumn();
        std::cout << "시간 또는 요일을 입력해라: ";
        std::cin >> tiwe;
        rr.maxCrime(tiwe);
        rr.minCrime(tiwe);
    }
    void showAgeGender()
    {
        std::string agse;
        AgeGender rr(mDB);
        rr.showColumn();
        std::cout << "찾고자 하는 대상 범위를 입력해라: ";
        std::cin >> agse;
        rr.maxCrime(agse);
        rr.minCrime(agse);
    }
    void loginAccount(const std::string& id, const std::string& pw)
    {
        mDB.setAccount(id,pw);
        mDB.connect();
    }
    void showCrime()
    {
        std::string choice;
        Crime rr(mDB);
        rr.showColumn();
        std::cout << "입력: ";
        std::cin >> choice;
        rr.showMaxMin_Age(choice);
        rr.showMaxMin_Pla(choice);
        rr.showMaxMin_Reg(choice);
        rr.showMaxMin_Tim(choice);
        rr.showMaxMin_Wea(choice);
    }
};

int main(void)
{
    std::string id = "OPER";
    std::string pw = "1357";
    Handler user;
    user.loginAccount(id, pw);
    int choice;

    while (true)
    {
        std::cout << "1) 지역별 범죄통계\n2) 시간별 범죄 통계\n3) 장소별 범죄 통계\n4) 성별별 범죄 통계";
        std::cout << std::endl << "5) 특정 범죄의 통계 조회\n6) 종료\n";
        std::cout << "입력: ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                user.showRegionMaxNmin();
                break;
            case 2:
                user.showTimeWeek();
                break;
            case 3:
                user.showPlaceMaxNmin();
                break;
            case 4:
                user.showAgeGender();
                break;
            case 5:
                user.showCrime();
                break;
            case 6:
                exit(0);
        }
    }
}
