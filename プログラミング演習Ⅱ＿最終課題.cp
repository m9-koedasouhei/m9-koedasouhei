//
//  main.cpp
//
//
//  Created by 小枝蒼平 on 2021/08/07.
//
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#define DECK 6
#define CARD 52
#define NUM DECK*CARD


struct BOX{
    private:
        int card_box[NUM];
        int card_num;

    public:
        BOX(){
            for(int a = 0; a < NUM; a++){
                card_box[a] = -1;
            }
            std::random_device rnd;
            for(int a = 0; a < NUM; a++){
                while(1){
                    int place = rnd()%(NUM);
                    if(card_box[place] == -1){
                        card_box[place] = a;
                        break;
                    }
                }
            }
            card_num = NUM;
        }
    
        void show_box(bool type){
            if(type){
                for(int a = 0; a < card_num; a++){
                    std::cout << card_box[a] << ' ';
                }
                std::cout << std::endl;
            }else{
                for(int a = 0; a < NUM; a++){
                    std::cout << card_box[a] << ' ';
                }
                std::cout << std::endl;
            }
        }
    
        int draw_card(){
            if(card_num == 0){
                std::cout << "NoStackError\nShoe.card_num" << std::endl;
                return -1;
            }
            
            int top = card_box[0];
            for(int a = 0; a < card_num-1; a++){
                card_box[a] = card_box[a+1];
            }
            card_box[card_num-1] = -1;
            card_num--;
            return top;
        }
};


struct Player{

    private:
        std::vector<int> hand;
        int hand_num;

    public:
    Player(){
            hand_num = 0;
        }
        int calc(){
            int *data;
            data = new int[hand_num];
            for(int a = 0; a < hand_num; a++){
                if(hand[a]%13 < 10){
                    data[a] = hand[a]%13+1;
                }
                else{
                    data[a] = 10;
                }
            }
            std::sort(data,data+hand_num);
            int score = 0;
            for(int a = 1; a < hand_num; a++){
                score += data[a];
            }
            if(data[0] == 1){
                if(score+11 < 22){
                    score += 11;
                }else{
                    score += 1;
                }
            }else{
                score += data[0];
            }
            if(score > 21){
                score = 0;
            }

            delete[] data;
            return score;
        }
        void hit(BOX *box){
            hand.push_back(box -> draw_card());
            hand_num++;
        }
        void show_hand(){
            std::cout << "手札: ";
            for(int a = 0; a < hand_num; a++){
                int type = (hand[a]%52)/13;
                switch(type){
                    case 0:
                        std::cout << "スペードの";
                        break;
                        
                    case 1:
                        std::cout << "ハートの";
                        break;
                        
                    case 2:
                        std::cout << "ダイヤの";
                        break;

                    case 3:
                        std::cout << "クラブの";
                        break;
                        
                    default:
                        std::cout << "DefTypeError\nPlayer.show_hand" << std::endl;
                        break;
                }
                std::cout << hand[a]%13+1 << " ";
            }
            std::cout << std::endl;
            std::cout << "合計点: " << calc() << std::endl;
        }
    
        bool play(BOX *box){
            while(calc()){
                //入力
                std::string str;
                std::cin >> str;
                if(str == "hit"){
                    hit(box);
                    std::cout << "------------------------" << std::endl;
                    std::cout << "プレーヤー" << std::endl;
                    show_hand();
                    std::cout << "------------------------" << std::endl;
                }else if(str == "stand"){
                    return true;
                }
            }
            return false;
        }
};

struct Dealer{

    private:
        std::vector<int> hand;
        int hand_num;

    public:
        Dealer(){
            hand_num = 0;
        }
        int calc(){
            int *data;
            data = new int[hand_num];
            for(int i = 0; i < hand_num; i++){
                if(hand[i]%13 < 10){
                    data[i] = hand[i]%13+1;
                }else{
                    data[i] = 10;
                }
            }
            std::sort(data,data+hand_num);
            int score = 0;
            for(int i = 1; i < hand_num; i++){
                score += data[i];
            }
            if(data[0] == 1){
                if(score+11 < 22){
                    score += 11;
                }else{
                    score += 1;
                }
            }else{
                score += data[0];
            }
            if(score > 21){
                score = 0;
            }

            delete[] data;
            return score;
        }
        void hit(BOX *box){
            hand.push_back(box -> draw_card());
            hand_num++;
        }
    
        void show_hand(){
            std::cout << "手札: ";
            for(int i = 0; i < hand_num; i++){
                int type = (hand[i]%52)/13;
                switch(type){
                    case 0:
                        std::cout <<"スペードの";
                        break;
                    case 1:
                        std::cout <<"ハートの";
                        break;
                    case 2:
                        std::cout <<"ダイヤの";
                        break;
                    case 3:
                        std::cout <<"クラブの";
                        break;
                    default:
                        std::cout << "DefTypeError\nPlayer.show_hand" << std::endl;
                        break;
                }
                std::cout << hand[i]%13+1 << " ";
            }
            std::cout << std::endl;
            std::cout << "合計点: " << calc() << std::endl;
        }
    
        void play(BOX *box){
            while(calc() < 17 && calc() > 0){
                hit(box);
                std::cout << "hit" << std::endl;
                std::cout << "-------------------------" << std::endl;
                std::cout << "ディーラー" << std::endl;
                show_hand();
                std::cout << "-------------------------" << std::endl;
            }
        }
};

void score(Player player, Dealer dealer){

    if(player.calc() > dealer.calc()){
        std::cout << "勝利!おめでとう" << std::endl;
    }else if(player.calc() < dealer.calc()){
        std::cout << "敗北,,,残念！" << std::endl;
    }else{
        std::cout << "引き分け．もう一回遊んでね！" << std::endl;
    }
}

int main(){
    BOX box;
    Player player;
    Dealer dealer;

    std::cout << "-------------------------" << std::endl;
    std::cout << "Blackjackスタート！" << std::endl;
    player.hit(&box);std::cout << "プレイヤー" << std::endl;
    player.show_hand();
    std::cout << "-------------------------" << std::endl;

    
    dealer.hit(&box);
    std::cout << "-------------------------" << std::endl;
    std::cout << "ディーラー" << std::endl;
    dealer.show_hand();
    std::cout << "-------------------------" << std::endl;

    player.hit(&box);
    std::cout << "-------------------------" << std::endl;
    std::cout << "プレイヤー" << std::endl;
    player.show_hand();
    std::cout <<"ヒットするときはhit,スタンドするときはstandと打ってください"<< std::endl;
    std::cout << "-------------------------" << std::endl;

    dealer.hit(&box);

    if(player.play(&box)){
        std::cout << "-------------------------" << std::endl;
        std::cout << "ディーラー" << std::endl;
        dealer.show_hand();
        std::cout << "-------------------------" << std::endl;

        dealer.play(&box);
        score(player,dealer);
    }
    else{
        std::cout << "バースト！敗北" << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
    return 0;
}
