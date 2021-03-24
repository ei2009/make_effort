#include <bits/stdc++.h>
#include <unistd.h>
#include <random>
using namespace std;
random_device rnd;     // 非決定的な乱数生成器を生成
mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
struct vigor{
    int number_of_players; //プレイヤーの人数
    int number_of_skills=18; //技の数
    int number_of_abnormals=5; //状態異常の数
    int default_hp=50; //体力の初期値
    int shake_wide=1; //揺れる数字の振れ幅
    int poison_number=0; //どくのビット桁
    int eleci_number=1; //まひのビット桁
    int sleep_number=2; //ねむりのビット桁
    int joint_number=3; //関節痛のビット桁
    int muscle_number=4; //ムキムキのビット桁
    int poison_power=3; //どくで1ターンあたりに減るデフォルトの体力
    int eleci_per=3; //まひで行動できなくなる確率の分母
    int sleep_per=2; //ねむる確率の分母
    int sleep_time=2; //ねむるデフォルトのターン数
    int normal_attack_number=1; //ノーマルアタックの技番号
    int fire_wave_number=2; //ファイアウェーブの技番号
    int poison_mist_number=3; //ポイズンミストの技番号
    int eleci_shock_number=4; //エレキショックの技番号
    int invite_dream_number=5; //インバイトドリームの技番号
    int hiza_kakkun_number=6; //ヒザカックンの技番号
    int have_medicine_number=7; //ハブメディシンの技番号
    int touch_iron_number=8; //タッチアイロンの技番号
    int sippu_hattoke_number=9; //シップハットケの技番号  
    int final_flash_number=10; //ファイナルフラッシュの技番号
    int clean_heal_number=11; //クリーンヒールの技番号
    int hundred_burst_number=12; //ハンドレッドバーストの技番号
    int core_dump_number=13; //コアダンプの技番号
    int what_happened_number=14; //ワットハップンドの技番号
    int coin_toss_number=15; //コイントスの技番号
    int throw_bomb_number=16; //スローボムの技番号    
    int lift_dumbbell_number=17; //リフトダンベルの技番号
    int bear_abnormal_number=18; //ベアーアブノーマルの技番号
    int normal_attack_power=10; //ノーマルアタックのデフォルトのダメージ
    int fire_wave_power=5; //ファイアウェーブのデフォルトのダメージ
    int final_flash_count; //ファイナルフラッシュの残り回数
    int clean_heal_power=10; //クリーンヒールの回復量
    int burst_per=100; //ハンドレッドバーストの命中率の分母
    int coin_toss_power=16; //コイントスのデフォルトのダメージ
    int coin_toss_per=2; //コイントスの命中率の分母
    int throw_bomb_power=25; //スローボムのデフォルトのダメージ
    int bear_abnormal_power=13; //ベアーアブノーマルのデフォルトのダメージ
    vector<int> player_hp; //プレイヤーの体力
    vector<int> player_form; //プレイヤーの状態異常を管理するビット
    vector<int> number_of_use_skills; //各プレイヤーが使用可能なスキルの数
    vector<int> player_sleep; //各プレイヤーの眠るターン数
    vector<int> player_muscle; //各プレイヤーのコミットするターン数
    vector<string> player_name; //プレイヤーの名前
    vector<string> skill_name; //スキルの名前
    vector<string> abnormal_name; //状態異常の名前
    set<int> skill; //抽選された技の番号
    vigor(int n){ //コンストラクト宣言
        number_of_players=n;
        player_hp.resize(n+1);
        player_form.resize(n+1);
        player_name.resize(n+1);
        number_of_use_skills.resize(n+1);
        player_sleep.resize(n+1);
        player_muscle.resize(n+1);
        skill_name.resize(number_of_skills+1);
        abnormal_name.resize(number_of_abnormals);
        for(int i=1;i<=n;i++){
            player_hp[i]=default_hp;
            player_form[i]=0;
            number_of_use_skills[i]=4;
            player_sleep[i]=0;
            player_muscle[i]=0;
        }
        enter_skill_name();
        enter_abnormal_name();
        uniform_int_distribution<> randflash(1,10);
        final_flash_count=randflash(mt);
        return;
    }
    void enter_skill_name(){ //技名の決定
        skill_name[normal_attack_number]="Normal Attack";
        skill_name[fire_wave_number]="Fire Wave";
        skill_name[poison_mist_number]="Poison Mist";
        skill_name[eleci_shock_number]="Eleci Shock";
        skill_name[invite_dream_number]="Invite Dream";
        skill_name[hiza_kakkun_number]="Hiza Kakkun";
        skill_name[have_medicine_number]="Have Medicine";
        skill_name[touch_iron_number]="Touch Iron";
        skill_name[sippu_hattoke_number]="Sippu Hattoke";
        skill_name[final_flash_number]="Final Flash";
        skill_name[clean_heal_number]="Clean Heal";
        skill_name[hundred_burst_number]="Hundred Burst";
        skill_name[core_dump_number]="Core Dump";
        skill_name[what_happened_number]="What Happened";
        skill_name[coin_toss_number]="Coin Toss";
        skill_name[throw_bomb_number]="Throw Bomb";
        skill_name[lift_dumbbell_number]="Lift Dumbbell";
        skill_name[bear_abnormal_number]="Bear Abnormal";
        return;
    }
    void enter_abnormal_name(){ //状態異常の名前の決定
        abnormal_name[poison_number]="どく";
        abnormal_name[eleci_number]="まひ";
        abnormal_name[sleep_number]="ねむり";
        abnormal_name[joint_number]="関節痛";
        abnormal_name[muscle_number]="ムキムキ";
        return;
    }
    void skill_display(int i){ //技の表示
        cout<<"行動を選択"<<endl;
        int j=1;
        for(auto it=skill.begin();it!=skill.end();it++){
            cout<<j<<" : "<<skill_name[*it]<<endl;
            j++;
        }
        return;
    }
    void skill_enter(int i,int command){ //技の発動
        if(command==normal_attack_number){
            normal_attack(i);
        }
        else if(command==fire_wave_number){
            fire_wave(i);
        }
        else if(command==poison_mist_number){
            poison_mist(i);
        }
        else if(command==eleci_shock_number){
            eleci_shock(i);
        }
        else if(command==invite_dream_number){
            invite_dream(i);
        }
        else if(command==hiza_kakkun_number){
            hiza_kakkun(i);
        }
        else if(command==have_medicine_number){
            have_medicine(i);
        }
        else if(command==touch_iron_number){
            touch_iron(i);
        }
        else if(command==sippu_hattoke_number){
            sippu_hattoke(i);
        }
        else if(command==final_flash_number){
            final_flash(i);
        }
        else if(command==clean_heal_number){
            clean_heal(i);
        }
        else if(command==hundred_burst_number){
            hundred_burst(i);
        }
        else if(command==core_dump_number){
            core_dump(i);
        }
        else if(command==what_happened_number){
            what_happened(i);
        }
        else if(command==coin_toss_number){
            coin_toss(i);
        }
        else if(command==throw_bomb_number){
            throw_bomb(i);
        }
        else if(command==lift_dumbbell_number){
            lift_dumbbell(i);
        }
        else if(command==bear_abnormal_number){
            bear_abnormal(i);
        }
        return;
    }
    bool game_set(){ //決着の確認
        int alive=0;
        for(int i=1;i<=number_of_players;i++){
            if(player_hp[i]>0){
                alive++;
            }
        }
        if(alive<=1){
            return true;
        }
        return false;
    }
    bool name_check(int i,string s){ //名前の重複の確認
        for(int j=1;j<i;j++){
            if(player_name[j]==s){
                return false;
            }
        }
        return true;
    }
    void name_enter(int i,string s){ //名前の入力
        player_name[i]=s;
        return;
    }
    string name_back(int i){ //名前を返す
        return player_name[i];
    }
    bool drow_judge(){ //引き分けの判定 
        int aliver=0;
        for(int i=1;i<=number_of_players;i++){
            if(player_alive(i)){
                aliver++;
            }
        }
        if(aliver==1){
            return true;
        }
        return false;
    }
    string winner_back(){ //勝者の名前を返す
        for(int i=1;i<=number_of_players;i++){
            if(player_hp[i]>0){
                return player_name[i];
            }
        }
        return "0";
    }
    bool player_alive(int i){ //生存の確認
        if(player_hp[i]>0){
            return true;
        }
        else{
            return false;
        }
    }
    bool all_death(){ //生存者の有無
        for(int i=1;i<=number_of_players;i++){
            if(player_alive(i)){
                return false;
            }
        }
        return true;
    }
    int hp_back(int i){ //体力を返す
        return player_hp[i];
    }
    void hp_display(int i){ //残りHPの表示
        if(player_hp[i]<=0){
            cout<<player_name[i]<<"の残りHP: "<<0<<endl<<endl;
            cout<<player_name[i]<<"は倒れた！"<<endl<<endl;
        }
        else{
            cout<<player_name[i]<<"の残りHP: "<<player_hp[i]<<endl<<endl;
        }
        sleep(1);
        return;
    }
    void player_damage(int t,int power){ //ダメージ処理
        if(player_form[t]&(1<<muscle_number)){
            cout<<player_name[t]<<"の筋肉は攻撃を通さない！"<<endl<<endl;
            sleep(1);
        }
        else{
            int damage=shake_number(power);
            if(player_hp[t]-damage<=0){
                cout<<player_name[t]<<"に"<<player_hp[t]<<"のダメージ！"<<endl<<endl;
            }
            else{
                cout<<player_name[t]<<"に"<<damage<<"のダメージ！"<<endl<<endl;
            }
            sleep(1);
            player_hp[t]-=damage;
            hp_display(t);
        }
        return;
    }
    void turn_start(int i){ //ターン開始時の処理
        cout<<name_back(i)<<"のターン！"<<endl<<endl;
        sleep(1);
        if(player_form[i]&(1<<sleep_number)){
            sleep_ing(i);
        }
        else if(player_form[i]&(1<<eleci_number)&&!eleci_ing(i)){
            cout<<"しかし"<<player_name[i]<<"は体が痺れて動けない！"<<endl<<endl;
        }
        else{
            if(player_form[i]&(1<<joint_number)){
                joint_ing(i);
            }
            if(player_form[i]&(1<<muscle_number)){
                muscle_ing(i);
            }
            cout<<"残りHP : "<<hp_back(i)<<endl;
            cout<<"状態異常 : ";
            for(int j=0;j<number_of_abnormals;j++){
                if(player_form[i]&(1<<j)){
                    cout<<abnormal_name[j]<<" ";
                }
            }
            cout<<endl<<endl;
            skill.erase(skill.begin(),skill.end());
            uniform_int_distribution<> randskill(1,number_of_skills);
            while(skill.size()<number_of_use_skills[i]){
                int skill_number=randskill(mt);
                skill.insert(skill_number);
            }
            skill_display(i);
            int command;
            string command_false;
            do{
                cin>>command_false;
                if(!judge_number(command_false,1,number_of_use_skills[i])){
                    cout<<"1~"<<number_of_use_skills[i]<<"までの数字で入力してください"<<endl<<endl;
                    skill_display(i);
                }
            }while(!judge_number(command_false,1,number_of_use_skills[i]));
            command=back_number(command_false);
            auto it=skill.begin();
            for(int j=1;j<command;j++){
                it++;
            }
            skill_enter(i,*it);
        }
        return;
    }
    void turn_end(int i){ //ターン終了時の処理
        if(player_alive(i)){
            if(player_form[i]&(1<<poison_number)){ 
                poison_ing(i);
            }
            if(player_form[i]&(1<<muscle_number)){
                
            }
        }
        cout<<"--------------------"<<endl<<endl;
        return;
    }
    int enter_target(int i){ //攻撃対象の選択
        cout<<"対象を選択"<<endl;
        vector<int> aliving;
        int aliver=0;
        for(int j=1;j<=number_of_players;j++){
            if(player_alive(j)&&j!=i){
                aliver++;
                cout<<aliver<<" : "<<player_name[j]<<"   残りHP: "<<player_hp[j]<<endl;
                aliving.push_back(j);
            }
        }
        string command_false="0";
        do{
            cin>>command_false;
            if(!judge_number(command_false,1,aliver)){
                cout<<"1~"<<aliver<<"の数字で入力してください"<<endl;
            }
        }while(!judge_number(command_false,1,aliver));
        int command=back_number(command_false);
        return aliving[command-1];
    }
    void poison_start(int i){ //どくの発動
        cout<<player_name[i]<<"はどく状態になった！"<<endl<<endl;
        sleep(1);
        player_form[i]|=(1<<poison_number);
        return;
    }
    void poison_ing(int i){ //どくの進行
        cout<<player_name[i]<<"の体をどくがむしばむ！"<<endl<<endl;
        sleep(1);
        player_damage(i,poison_power);
        return;
    }
    void poison_end(int i){ //どくの解除
        cout<<player_name[i]<<"のどくがなおった！"<<endl<<endl;
        sleep(1);
        player_form[i]&=~(1<<poison_number);
        return;
    }
    void eleci_start(int i){ //まひの発動
        cout<<player_name[i]<<"はまひ状態になった！"<<endl<<endl;
        sleep(1);
        player_form[i]|=(1<<eleci_number);
        return;
    }
    bool eleci_ing(int i){ //まひの進行
        uniform_int_distribution<> randeleci(1,eleci_per);
        int re=randeleci(mt);
        if(re==eleci_per){
            return false;
        }
        else{
            return true;
        }
    }
    void eleci_end(int i){ //まひの解除
        cout<<player_name[i]<<"のまひがなおった！"<<endl<<endl;
        sleep(1);
        player_form[i]&=~(1<<eleci_number);
    }
    void sleep_start(int i){ //ねむりの発動
        cout<<player_name[i]<<"はねむり状態になった！"<<endl<<endl;
        sleep(1);
        int time=shake_number(sleep_time);
        player_form[i]|=(1<<sleep_number);
        player_sleep[i]=time;
        return;
    }
    void sleep_ing(int i){ //ねむりの進行分母
        player_sleep[i]--;
        if(player_sleep[i]<=0){
            sleep_end(i);
        }
        else{
            cout<<"しかし"<<player_name[i]<<"は眠っている！"<<endl<<endl;
        }
        return;
    }
    void sleep_end(int i){ //ねむりの解除
        cout<<player_name[i]<<"は目を覚ました！"<<endl<<endl;
        sleep(1);
        player_form[i]&=~(1<<sleep_number);
        player_sleep[i]=0;
        return;
    }
    void joint_start(int i){ //関節痛の発動
        cout<<player_name[i]<<"は関節痛になった！"<<endl<<endl;
        sleep(1);
        player_form[i]|=(1<<joint_number);
        number_of_use_skills[i]--;
        return;
    }
    void joint_ing(int i){ //関節痛の進行
        cout<<player_name[i]<<"は膝が痛くて技が"<<number_of_use_skills[i]<<"種類しか出せない！"<<endl<<endl;
        sleep(1);
        return;
    }
    void joint_end(int i){ //関節痛の解除
        cout<<player_name[i]<<"の膝の痛みが治った！"<<endl<<endl;
        sleep(1);
        player_form[i]&=~(1<<joint_number);
        number_of_use_skills[i]++;
        return;
    }
    void muscle_start(int i){ //ムキムキの発動
        cout<<player_name[i]<<"はムキムキになった！"<<endl<<endl;
        sleep(1);
        player_form[i]|=(1<<muscle_number);
        player_muscle[i]=1;
        return;
    }
    void muscle_ing(int i){ //ムキムキの進行
        player_muscle[i]--;
        if(player_muscle[i]<=0){
            muscle_end(i);
        }
        return;
    }
    void muscle_end(int i){ //ムキムキの解除
        cout<<player_name[i]<<"はリバウンドしてしまった！"<<endl<<endl;
        sleep(1);
        player_form[i]&=~(1<<muscle_number);
        player_muscle[i]=0;
        return;
    }
    void normal_attack(int i){ //ノーマルアタック
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        player_damage(t,normal_attack_power);
        return;
    }
    void fire_wave(int i){ //ファイアウェーブ
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"は炎の波を放った！"<<endl<<endl;
        sleep(1);
        for(int j=1;j<=number_of_players;j++){
            if(player_alive(j)&&j!=i){
                player_damage(j,fire_wave_power);
            }
        }
        return;
    }
    void poison_mist(int i){ //ポイズンミスト
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"は毒霧を吹き出した！"<<endl<<endl;
        sleep(1);
        if(player_form[t]&(1<<poison_number)){
            cout<<"しかし"<<player_name[t]<<"はすでにどく状態だ！"<<endl<<endl;
            sleep(1);
        }
        else{
            poison_start(t);
        }
        return;
    }
    void eleci_shock(int i){ //エレキショック
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[t]<<"の体に電流が走る！"<<endl<<endl;
        sleep(1);
        if(player_form[t]&(1<<eleci_number)){
            cout<<"しかし"<<player_name[t]<<"はすでにまひ状態だ！"<<endl<<endl;
            sleep(1);
        }
        else{
            eleci_start(t);
        }
        return;
    }
    void invite_dream(int i){ //インバイトドリーム
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"は美声を響かせ子守唄を歌った！"<<endl<<endl;
        sleep(1);
        uniform_int_distribution<> randsleep(1,sleep_per);
        int re=randsleep(mt);
        if(player_form[t]&(1<<sleep_number)){
            cout<<"しかし"<<player_name[t]<<"はすでにねむり状態だ！"<<endl<<endl;
            sleep(1);
        }
        else if(re!=sleep_per){
            cout<<"しかし"<<player_name[t]<<"は眠らなかった！"<<endl<<endl;
            sleep(1);
        }
        else{
            sleep_start(t);
        }
        return;
    }
    void hiza_kakkun(int i){ //ヒザカックン
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[t]<<"の膝からなってはいけない音がなった！"<<endl<<endl;
        sleep(1);
        if(player_form[t]&(1<<joint_number)){
            cout<<"しかし"<<player_name[t]<<"はすでに膝が痛い！"<<endl<<endl;
            sleep(1);
        }
        else{
            joint_start(t);
        }
        return;
    }  
    void have_medicine(int i){ //ハブメディシン
        cout<<player_name[i]<<"はおクスリを吸った！"<<endl<<endl;
        sleep(1);
        if(player_form[i]&(1<<poison_number)){
            poison_end(i);
        }
        else{
            cout<<"しかし"<<player_name[i]<<"はどく状態ではない！"<<endl<<endl;
            sleep(1);
        }
        return;
    }
    void touch_iron(int i){ //タッチアイロン
        cout<<player_name[i]<<"は廊下の水道管に触れた！"<<endl<<endl;
        sleep(1);
        if(player_form[i]&(1<<eleci_number)){
            eleci_end(i);
        }
        else{
            cout<<"しかし"<<player_name[i]<<"はまひ状態ではない！"<<endl<<endl;
            sleep(1);
        }
        return;
    }
    void sippu_hattoke(int i){ //シップハットケ
        cout<<"ジンジンきたきたぁー！！"<<endl<<endl;
        sleep(1);
        if(player_form[i]&(1<<joint_number)){
            joint_end(i);
        }
        else{
            cout<<"しかし"<<player_name[i]<<"は関節痛ではない！"<<endl<<endl;
            sleep(1);
        }
        return;
    }
    void final_flash(int i){ //ファイナルフラッシュ
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"によって封印が1つ解かれた...！"<<endl<<endl;
        sleep(1);
        final_flash_count--;
        if(final_flash_count<=0){
            cout<<"まばゆい光が全てを消し去った！"<<endl<<endl;
            sleep(1);
            for(int j=1;j<=number_of_players;j++){
                if(j!=i){
                    player_hp[j]=0;
                }
            }
        }  
        else{
            cout<<"もうすぐ何かが起こりそうだ...！"<<endl<<endl;
            sleep(1);
        }
        return;
    }
    void clean_heal(int i){ //クリーンヒール
        cout<<player_name[i]<<"は自身を浄化した！"<<endl<<endl;
        sleep(1);
        int damage=shake_number(clean_heal_power);
        if(player_hp[i]+damage>=default_hp){
            damage=default_hp-player_hp[i];
        }
        cout<<player_name[i]<<"は"<<damage<<"回復した！"<<endl<<endl;
        sleep(1);
        player_hp[i]+=damage;
        if(player_hp[i]>default_hp){
            player_hp[i]=default_hp;
        }
        hp_display(i);
        return;
    }
    void hundred_burst(int i){ //ハンドレッドバースト
        uniform_int_distribution<> randburst(1,burst_per);
        int rb=randburst(mt);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<"あの大技が！"<<endl<<endl;
        sleep(1);
        cout<<"なんと！"<<endl<<endl;
        sleep(1);
        cout<<"なんとなんと！"<<endl<<endl;
        sleep(3);
        if(rb==burst_per){
            cout<<"でたぁぁぁぁぁぁ！！！！"<<endl<<endl;
            sleep(1);
            for(int j=1;j<=number_of_players;j++){
                if(j!=i){
                    player_hp[j]=0;
                }
            }
        }
        else{
            cout<<"出ませんでした〜"<<endl<<endl;
            sleep(1);
        }
        return;
    }
    void core_dump(int i){ //コアダンプ
        sleep(1);
        cout<<"/builddir/build/BUILD/gcc-8.3.1-20191121/obj-x86_64-redhat-linux/x86_64-redhat-linux/libstdc++-v3/include/bits/basic_string.h:1067: std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::reference std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::operator[](std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::size_type) [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>; std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::reference = char&; std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::size_type = long unsigned int]: Assertion '__pos <= size()' failed."<<endl;
        sleep(1);
        cout<<"中止 (コアダンプ)"<<endl<<"bash-4.4(luke):~/prog/doryoku"<<endl<<"1005:{ei2009}$"<<flush;
        sleep(5);
        cout<<endl<<endl<<"なんちゃって"<<endl<<endl;
        sleep(1);
        return;
    }
    void what_happened(int i){ //ワットハップンド
        int rws,rwp;
        cout<<"何かが起こる！"<<endl<<endl;
        sleep(1);
        uniform_int_distribution<> randwhatplayers(1,number_of_players);
        uniform_int_distribution<> randwhatskills(1,number_of_skills);
        do{
            rwp=randwhatplayers(mt);
        }while(!player_alive(rwp));
        do{
            rws=randwhatskills(mt);
        }while(rws==what_happened_number);
        skill_enter(rwp,rws);
        return;
    }
    void coin_toss(int i){ //コイントス
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"は渾身の一撃を繰り出した！"<<endl<<endl;
        sleep(1);
        uniform_int_distribution<> randcoin(1,coin_toss_per);
        int rc=randcoin(mt);
        if(rc==coin_toss_per){
            player_damage(t,coin_toss_power);
        }   
        else{
            cout<<"しかし当たらなかった！"<<endl<<endl;
            sleep(1);
        }
        return;
    }
    void throw_bomb(int i){ //スローボム
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"は爆弾を放り投げた！"<<endl<<endl;
        sleep(1);
        uniform_int_distribution<> randbomb(1,number_of_players);
        int rb=randbomb(mt);
        while(!player_alive(rb)){
            rb=randbomb(mt);
        }
        if(rb==i){
            cout<<"しかし返ってきた！"<<endl<<endl;
            sleep(1);
        }
        player_damage(rb,throw_bomb_power);
        return;
    }
    void lift_dumbbell(int i){ //リフトダンベル
        cout<<player_name[i]<<"は結果にコミットした！"<<endl<<endl;
        sleep(1);
        if(player_form[i]&(1<<muscle_number)){
            cout<<"しかし"<<player_name[i]<<"は既にムキムキだ！"<<endl<<endl;
            sleep(1);
        }
        else{
            muscle_start(i);
        }
        return;
    }
    void bear_abnormal(int i){ //ベアーアブノーマル
        int t=enter_target(i);
        cout<<player_name[i]<<"の攻撃！"<<endl<<endl;
        sleep(1);
        cout<<player_name[i]<<"は何かを犠牲にしつつ攻撃した！"<<endl<<endl;
        sleep(1);
        player_damage(t,bear_abnormal_power);
        uniform_int_distribution<> randabnormal(1,number_of_abnormals);
        int ra=randabnormal(mt)-1;
        while(player_form[i]&(1<<ra)){
            int ra=randabnormal(mt)-1;
        }
        if(ra==poison_number){
            poison_start(i);
        }
        else if(ra==eleci_number){
            eleci_start(i);
        }
        else if(ra==sleep_number){
            sleep_start(i);
        }
        else if(ra==joint_number){
            joint_start(i);
        }
        else if(ra==muscle_number){
            muscle_start(i);
        }
        return;
    }
    bool judge_number(string f,int minv,int maxv){ //入力が規定の範囲内の数字であるかの判定
        int tn=0;
        if(f[0]=='-'&&f.size()>1){
            for(int i=1;i<f.size();i++){
                if(f[i]<'0'||'9'<f[i]){
                    return false;
                }
            }
            int j=f.size()-2;
            for(int i=1;i<f.size();i++){
                tn-=(f[i]-'0')*pow(10,j);
                j--;
            }
        }
        else{
            for(int i=0;i<f.size();i++){
                if(f[i]<'0'||'9'<f[i]){
                    return false;
                }
            }
            int j=f.size()-1;
            for(int i=0;i<f.size();i++){
                tn+=(f[i]-'0')*pow(10,j);
                j--;
            }
        }
        if(tn<minv||maxv<tn){
            return false;
        }
        else{
            return true;
        }
    }
    int back_number(string f){ //数字を返す
        int tn=0,j=f.size()-1;
        if(f[0]=='-'){
            int j=f.size()-2;
            for(int i=1;i<f.size();i++){
                tn-=(f[i]-'0')*pow(10,j);
                j--;
            }
        }
        else{
            int j=f.size()-1;
            for(int i=0;i<f.size();i++){
                tn+=(f[i]-'0')*pow(10,j);
                j--;
            }
        }
        return tn;
    }  
    int shake_number(int i){ //数字を揺らす
        int minv=0,maxv=0;
        minv-=shake_wide;
        maxv+=shake_wide;
        uniform_int_distribution<> randshake(minv,maxv);
        int rs=randshake(mt);
        return i+rs;
    }

};
bool judge_number(string f,int minv,int maxv){
    if(f.size()>1){
        return false;
    }
    int fn=f[0]-'0';
    if(fn<minv||maxv<fn){
        return false;
    }
    return true;
}
int back_number(string f){
    return f[0]-'0';
}  
int main(){
    int number_of_players;
    string number_false,name;
    uniform_int_distribution<> rand100(1, 100);
    
    do{
        cout<<"参加人数の入力(2人〜4人) : ";
        cin>>number_false;
        cout<<endl;
        if(!judge_number(number_false,2,4)){
            cout<<"参加できるのは2人~4人です"<<endl<<endl<<endl;
            sleep(1);
            continue;
        }
    }while(!judge_number(number_false,2,4));
    number_of_players=back_number(number_false);
    vigor func(number_of_players);
    int count=1;
    while(count<=number_of_players){
        cout<<count<<"人目のプレイヤーは名前を入力してください : ";
        cin>>name;
        cout<<endl;
        if(func.name_check(count,name)){
            func.name_enter(count,name);
            count++;
        }
        else{
            cout<<"その名前は既に使用されています"<<endl<<endl<<endl;
            sleep(1);
        }
    }
    uniform_int_distribution<> randplayer(1, number_of_players);
    int order=randplayer(mt);
    cout<<func.name_back(order)<<"からスタート！！！"<<endl<<endl;
    sleep(1);
    while(!func.game_set()){
        func.turn_start(order);
        func.turn_end(order);
        do{
            order++;
            if(order>number_of_players){
                order=1;
            }
        }while(!func.player_alive(order)&&!func.all_death());
    }
    if(func.drow_judge()){
        cout<<func.winner_back()<<"の勝利！"<<endl<<endl;
    }
    else{
        cout<<"引き分け！"<<endl<<endl;
    }
    sleep(2);
    return 0;
}