# Teris-battle
# Teris Battle Result Prediction

### Description
The goal of this project is to predict the result after input blocks on the game board.

### Main flow chart
![](https://i.imgur.com/mE1wNXF.png)

### Component
> 總共有三個類別:GameBoard, Table, Block。
* GameBoard
    *  `new_gameboard()`
        動態配置出大小為`row*col`的俄羅斯方掉落的區域     `gameboard`。
    * `bomb_gameboard()`
        當`gameboard`中有一列 i 滿了即消掉該列。
    * `print_gameboard()`
        印出遊戲的最後結果。
* Block
    * `create_hitset()`
        建立一`hitset`，記錄`block`在`gameboard`中從`pos1`移動至`pos2`會過的點。
* Table
    * nonzerotable:記錄gmaeboard中有堆方塊的地方。
    * bombtable:記錄gameboard中每一列的方塊數，以偵測有無列需要做消去。
    *  bomb_bombtable():當一列消去則更新bombtable。
    *  bomb_nonzerotable():當一列消去則更新nonzerotable。
    *  update_table():將block放上gameboard，nonzerotable及 bombtable。
    *  check_ishit(hitset):檢查hitset中有無已經有方塊佔據的位置。
    *  check_isbomb(hitset):檢查bombtable中，有無在gameboard中需要消去的列。

* Share function
    * `game_over()`
        以下三種情況發生時結束遊戲，印出gameboard結果。
    * invalid
        * 輸入錯誤的`block`名稱
        * 輸入超出`gameboard`範圍的位置
    * lose
        * block碰到gameboard頂端
    * end
        檔案讀到最後一行End
        * 流程
            在主程式中，讀取測資建立GameBoard物件，初始為利用`new_gameboard()`函式動態配置出二維向量`gameboard`所需的空間，以及`Table`物件，初始為建 立參考指向`GameBoard.gameboard`，一為向量`bombtable`及二為向量 `nonzerotable`。其中`nonzerotable`初始為`col`個`vector`，每個`vector`中有一值-1， 並在每次更新時利用`sort_table()`對每一`col`的`vector`由小到大進行排序，如此 一來只要抓每一`col`的最後一個元素，即可得到該`col`最高的列數。而 `bombtable`初始為有`col`個空間初始直接為零，當某一值等於`row`時，代表值所 屬的`index`，即`gameboard`的第`index`列已滿，進行消去。當測資所在檔案尚未結束時，利用`while`迴圈將每行`block`的`kind`及`position` 讀入。建立`Block`物件，利用`create_hitset()建立資料型態為`multimap`之`hitset` 記錄`block`從`pos1`到`pos2`移動時會經過的位置。將`hitset` 傳入 check_ishit()`，檢查在`nonzerotable`中是否有記錄`hitset`中的任一位置，若有，則代表`invalid`，遊戲終止。若無，則利用`update_table()`將block位置更新至`gameboard`,`nonzerotable`及`bombtable`上。利用`check_isbomb()`檢查`bombtable`中是否有列數 達到`row`值的`col`。若有，則回傳該`index`至`bomb_gameboard()`， `bomb_nonzerotable()`及`bomb_bombtable()`。其中`bomb_gameboard()`為複製一份 gameboard給二維向量`tmp`，將`tmp[index]`erase之後，新增初始值全為0的 `vector`給`tmp.end()`，最後將`gameboard`指向`tmp`。`bomb_nonzerotable`為將每一 `col`中`index`以上位址的值全部減一，最後把`index` erase。而 `bomb_bombtable()` 為將第index個位置`erase`，並新增一個0給最後一列。若無則回到while迴圈 讀取新的一行檔案。

### Command Line for running this project
g++ -o ${filename} -O2 -std=c++11 ${filename}.cpp
./${filename} ${testcase}.data
