# robosys_kadai1
ロボットシステム学　課題１
## 概要
電子ブザーを使用して、１~３を入力するとその回数分ブザーが鳴り、４を入力すると三三七拍子をするプログラムを作成しました。
コードは川鍋清志郎君のものを参考にしました。

## 動作環境
OS：Ubuntu 18.04

## 使用したもの
- Raspberry Pi 4
- ブレットボード
- 電子ブザー
- ジャンパー線×２

## 回路
以下の図のように回路を作成しました


## 動画
実際に動かしたときの動画は[こちら](https://www.youtube.com/watch?v=HaBOnk_5vlE&feature=youtu.be)です

## 実行手順
以下のコマンドを順番に行います。
### インストール
```
git clone https://github.com/Yuya-Takeuchi/robosys_kadai1.git
```
### ビルド
```
cd robosys_kadai1/
make
sudo insmod myled.ko
sudo chmod 666 /dev/myled0
```
### 実行
```
echo {1,2,3,4} > /dev/myled0
```
### 後処理
```
sudo rmmod myled
```

## ライセンス
[GNU General Public License v3.0](https://github.com/Yuya-Takeuchi/robosys_kadai1/blob/main/LICENSE) 
