## Phonetisaurus G2P - pybind11 binding ##

![](https://anaconda.org/cvrunmin/phonetisaurus-py/badges/version.svg) ![](https://anaconda.org/cvrunmin/phonetisaurus-py/badges/platforms.svg)

This repository is a fork from https://github.com/AdolfVonKleist/Phonetisaurus which focus on building Python binding using pybind11. This repo benefits from OpenFst package in anaconda.org which allows independency from version of OpenFst unless any breaking changes on api or dynamic linking.

The original Phonetisaurus repository contains scripts suitable for training, evaluating and using grapheme-to-phoneme
models for speech recognition using the OpenFst framework.  While scripts are cloned basically intact here, Only PhonetisaurusScript.h is exposed, and thus built for the binding. Such bindings may be used to extract individual multigram scores, alignments, and to dump the raw lattices in .fst format for each word.

If you want to train, compile, or evaluate G2P models using python, feel free to send pull request, or consider building with the original repo.

If you want to take a look at standalone distributions related to previous INTERSPEECH papers, as well as the complete, exported
final version of the old google-code repository are available via ```git-lfs``` in a separate
repository from the original author:
  * https://github.com/AdolfVonKleist/phonetisaurus-downloads


### Building ###

The following instruction is for Conda environment only. While building is possible without Conda, such situation requires OpenFst to be correctly installed for compiler to locate required header and library files.

Clone this repo into anywhere you like.

Create a new environment with provided `environment.yml`. This step ensure your machine could pull dependencies from the Internet for building:
```commandline
conda env create -f environment.yml
```

Build this repo using conda-build:
```commandline
conda build conda -c conda-forge
```

Install built package for testing:
```commandline
conda install -c local phonetisaurus-py
```

Inside `python/script`, test the manual model with the wrapper script:
```
$ ./phoneticize.py -m ~/example/cmudict.o8.fst -w testing
  11.24   T EH1 S T IH0 NG
  -------
  t:T:3.31
  e:EH1:2.26
  s:S:2.61
  t:T:0.21
  i:IH0:2.66
  n|g:NG:0.16
  <eps>:<eps>:0.01
```

### Usage ###

Install phonetisaurus-py into your Conda environment:
```commandline
conda install -c cvrunmin -c conda-forge phonetisaurus-py
```

Initialize a Phonetisaurus model with a G2P transducer (for example, `cmudict.o8.fst`):
```python
from phonetisaurus import PhonetisaurusModel

model = PhonetisaurusModel("cmudict.o8.fst")
```

Phoneticize a word into lists of phoneme:
```python
results = model.phoneticize('testing')
phonemes = [[model.find_osym(u) for u in result.uniques] for result in results]
```

### Difference from the binding of upstream repo ###

Members of the module exported is basically identicial, with naming changed to adapt python's convention
| Phonetisaurus | phontisaurus-py | notes |
| ---|---|---|
| PhonetisaurusScript|PhonetisaurusModel|Only change in class name as 'Model' should be clearer than 'Script' |
| Phoneticize|phoneticize||
| FindIsym|find_isym||
| FindOsym|find_osym||
| PathData|PathData||
| PathWeight|path_weight||
| PathWeights|path_weights||
| ILabels|input_labels|State clearly what I means|
| OLabels|output_labels|State clearly what O means|
| Uniques|uniques||
