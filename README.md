# Statistical-Language-Model
統計的言語モデルを作成します．

# 概要
(1) ngram モデルの推定<br>
夏目漱石「吾輩は猫である」の電子化テキストを用いて、単語の bigram, trigram モデルの確率を推定せよ。<br>

(2) 評価<br>
夏目漱石の「こころ」をテスト・セットとし、作成したモデルの test-set perplexity を計算せよ。<br>

# Bigram
訓練テキスト neko.num を使って、単語「て」(数値表現は 28)の直後に出現する単語の確率を neko.num に
出現するすべての単語(13,938 種類)に対して推定せよ。未知語に対する確率は推定しなくてよい。
すなわち、 13,938 種類の単語の条件付き確率の合計がちょうど 1.0 となるように推定する。
<br>モデル：bigram.model

# Trigram
上記の bigram モデルの推定を trigram に拡張した課題。単語「し」それに続く単語「て」(数値表現は 24
と 28)の直後に出現する単語の確率を neko.num に出現するすべての単語(13,938 種類)に対して推定せよ。
<br>モデル：trigram.model

# プログラム
kadai.py

# 手法
最尤推定法をベースにチューニングを行いました．

# 評価
評価用テストセット:kokoro.num<br>
評価用のテキストとして、夏目漱石「こころ」より抜粋した文集合(ファイル:kokoro.num)を用いる。neko.num と同様に、neko.dic に従って、各単語は数値に変換されている。ただし、neko.dic にない 単語については、数値「0」で表現されている。
## 評価実行方法
python kadai.py (モデル生成)

% cc pp.c -o pp -lm (評価用プログラムのコンパイル）
<br> 
./pp bigram.model -bi 28 < kokoro.num (bigram.modelを評価)
<br>
./pp trigram.model -tri 24 28 < kokoro.num (trigram.modelを評価)


# ライセンス
CopyRight (c) 2018 Shuto Kawabata

Released under the MIT licence

https://opensource.org/licenses/MIT

# 作成者
Shuto kawabata
