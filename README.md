# シューティングゲーム
## 概要
よくあるシューティングゲームです。C++の勉強がてら作ってみました。タイトルやクリア画面は作成していません。Dxlibを使用しています。
https://bituse.info/game/shot/3 を参考にさせていただきました。
## 遊び方
- スペースキーで弾を発射
- WASDで移動
- 敵を倒すとアイテムが出現
  - Sはスコアが増加
  - Pはパワーが増加
    - パワーが5以上で弾が3方向に
    - パワーが10になると敵を自動追尾する弾を発射する白い球が出現
- グレイズ(弾がキャラをかすめる)で得点がアップ
- 敵が50体出現した後にボスが出現
- ボスはHPによって行動パターンと攻撃パターンが変化
## 実際のプレイ動画
# ![ShootingProject](https://user-images.githubusercontent.com/45473854/208450666-5817e520-c017-4bd6-941f-a69272be2b37.gif)