#! /usr/bin/python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# Last modified: 2018-03-17 18:10:32

import pandas as pd
from matplotlib import pyplot

data = pd.read_table('./opt.txt', sep=' ')

fig, ax = pyplot.subplots()
data.plot("Hash_table_size", "append()", kind='bar', ax=ax, title="append")

for k, v in data.iterrows():
    ax.text(k, v["append()"], str(round(v["append()"], 4)))

fig.savefig("append.png")

fig, ax = pyplot.subplots()
data.plot("Hash_table_size", "findName()",
          kind='bar', ax=ax, title="findName")

for k, v in data.iterrows():
    ax.text(k, v["findName()"], str(v["findName()"]))

fig.savefig("findName.png", dpi=700)
