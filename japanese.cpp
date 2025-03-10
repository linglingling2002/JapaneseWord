#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>
#include <iomanip> // 包含 std::setw 和 std::left

/** 
 * 在同文件夹下的word.txt中输入。
 * 支持“とざん 登山 登山”格式
 * 也支持以下格式：
 *     ぼうはん
 *     防犯
 *     防止犯罪
 * 只要保证三个一组即可。
 * 
 *  本程序不把换行或空格作为单词, 有空则使用 “-” 或其他不影响阅读的符号占位即可。
 */

class Word{
private:
    std::string letter;
    std::string wordStage;
    std::string meaning;

public:
    Word(){
        letter = "";
        wordStage = "";
        meaning = "";
    }
    Word(std::string letter, std::string wordStage, std::string meaning) 
        : letter(letter), wordStage(wordStage), meaning(meaning){
        ;
    }
    void setLetter(std::string letter){
        this->letter = letter;
    }
    std::string getLetter(){
        return this->letter;
    }
    void setWordStage(std::string wordStage){
        this->wordStage = wordStage;
    }
    std::string getWordStage(){
        return this->wordStage;
    }
    void setMeaning(std::string meaning){
        this->meaning = meaning;
    }
    std::string getMeaning(){
        return this->meaning;
    }
    void printWord(){
        std::cout << std::left  // 左对齐
        << std::setw(20) << getLetter() << " | " << std::setw(12) << getWordStage() << " | " << std::setw(30) << getMeaning() << std::endl;
    }
};

void line(){
    for(int i = 0; i < 15; i++){
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------------" << std::endl;
    for(int i = 0; i < 15; i++){
        std::cout << std::endl;
    }
}

int main(){
    int mode = 0;
    int count = 0;
    std::vector<Word> wordGroup;
    char data[100];    
    std::ifstream inFile;
    inFile.open("word.txt");

    while(!inFile.eof()){
        Word newWord;
        std::string newStr;

        inFile >> data;
        newStr = data;
        newWord.setLetter(newStr);
        inFile >> data;
        newStr = data;
        newWord.setWordStage(newStr);
        inFile >> data;
        newStr = data;
        newWord.setMeaning(newStr);

        wordGroup.push_back(newWord);
    }

    do{
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "选择模式 输入1, 看假名写汉字模式; 输入2, 看汉字写假名模式; 输入3, 浏览模式; 输入0, 程序结束:";
        std::cin >> mode;

        if(0 == mode){
            break;
        }else if(3 == mode){
            for(int i = 0; i < wordGroup.size(); i++){
                wordGroup[i].printWord();
            }
        }else{
            std::cout << "输入默写个数 (单个单元最好不超过20) :";
            std::cin >> count;
            std::cout << "-------------------------------------------" << std::endl;

            std::vector<int> numbers;
            for (int i = 1; i <= count; i++) {
                numbers.push_back(i);
            }
            // 随机打乱顺序
            std::default_random_engine e(time(0));
            std::shuffle(numbers.begin(), numbers.end(), e);
            std::cout << std::endl;
    
            if(1 == mode){
                for(int i = 0; i < count; i++){
                    std::cout << std::left << std::setw(20) << wordGroup[numbers[i]].getLetter() << " | " << std::setw(12) << wordGroup[numbers[i]].getWordStage() << std::endl;
                }
                line();
                for(int i = 0; i < count; i++){
                    std::cout << wordGroup[numbers[i]].getLetter() << std::endl;
                }
            }else if(2 == mode){
                for(int i = 0; i < count; i++){
                    std::cout << std::left << std::setw(20) << wordGroup[numbers[i]].getLetter() << " | " << std::setw(12) << wordGroup[numbers[i]].getWordStage() << std::endl;
                }
                line();
                for(int i = 0; i < count; i++){
                    std::cout << wordGroup[numbers[i]].getWordStage() << std::endl;
                }
            }
        }
        
    }while(0 != mode);

    std::cout << "程序结束。" << std::endl;

    return 0;
}
