# Statistical-Language-Model
For making Statical language model from training data. 統計的言語モデルを作成します．

# 概要
(1) ngram モデルの推定<br>
夏目漱石「吾輩は猫である」の電子化テキストを用いて、単語の bigram, trigram モデルの確率を推定せよ。<br>

(2) 評価<br>
夏目漱石の「こころ」をテスト・セットとし、作成したモデルの test-set perplexity を計算せよ。<br>

# Bigram
訓練テキスト neko.num を使って、単語「て」(数値表現は 28)の直後に出現する単語の確率を neko.num に
出現するすべての単語(13,938 種類)に対して推定せよ。未知語に対する確率は推定しなくてよい。
すなわち、 13,938 種類の単語の条件付き確率の合計がちょうど 1.0 となるように推定する。

# Trigram
上記の bigram モデルの推定を trigram に拡張した課題。単語「し」それに続く単語「て」(数値表現は 24
と 28)の直後に出現する単語の確率を neko.num に出現するすべての単語(13,938 種類)に対して推定せよ。

# 評価
