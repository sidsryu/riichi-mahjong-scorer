# riichi-mahjong-scorer

[![Build Status](https://travis-ci.org/sidsryu/koikoi-scorer.svg?branch=master)][travis]
[![license](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)][license]

Japanese mahjong scorer in c++14

[license]: LICENSE 
[travis]: https://travis-ci.org/sidsryu/riichi-mahjong-scorer


## About Riichi Mahjong Scorer

리치마작 계산기입니다.

완성된 손패에서 판수와 부수를 알아냅니다.
오른 방식에 따라 지불해야하는 점수를 계산합니다.

추가 목표로 텐파이 상태 확인 및 대기패 찾기 기능이 들어갑니다.


## Goal

v1.0 목표

- [x] 점수 계산하기
- [x] 부수 계산하기
- [x] 판수 계산하기


## Installation

테스트 프레임워크로 [CppUTest][cpputest]를 사용합니다.
포함된 VS2015 프로젝트에서는 `/lib/cpputest` 위치에서 정적 라이브러리를 찾습니다. 
CppUTest는 수동으로 설치해야합니다.

CMake를 사용할 경우 CppUTest까지 함께 설치합니다.

```
cd Build
cmake ..
make
```


## Usage

### 손패 취급

```c++
#include <player-hand.h>

using namesapce mahjong;

PlayerHand h;

h.add(Tile::SouthWind);
h.add(Tile::SouthWind);

h.add(Tile::OneOfCharacters);
h.add(Tile::TwoOfCharacters);
h.add(Tile::ThreeOfCharacters);

h.add(Tile::FiveOfCircles);
h.add(Tile::FiveOfCircles);
h.add(Tile::RedFiveOfCircles);
h.bindTriplet({
    Tile::FiveOfCircles, Tile::FiveOfCircles, Tile::RedFiveOfCircles 
});

h.add(Tile::EightOfBamboos);
h.add(Tile::EightOfBamboos);
h.add(Tile::EightOfBamboos);
h.add(Tile::EightOfBamboos);
h.add(Tile::EightOfBamboos);
h.bindQuad({
    Tile::EightOfBamboos, Tile::EightOfBamboos, Tile::EightOfBamboos,
    Tile::EightOfBamboos 
});

h.add(Tile::SevenOfCharacters);
h.add(Tile::EightOfCharacters);
h.add(Tile::NineOfCharacters);
h.bindSequence({
    Tile::SevenOfCharacters, Tile::EightOfCharacters, Tile::NineOfCharacters 
});

```

### 점수 계산

```c++
#include "doubling-factor-counter.h"
#include "player-hand.h"
#include "wining-state.h"

using namespace mahjong;

PlayerHand h;
... // add tiles to hand

WiningState s;
s.selfDrawn();

// han: doubling factor
DoublingFactorCounter dc { h, s };
DoublingFactorReport r = dc.report();

// fu: minipoints
MinipointCounter mc { h, s };
int minipoints = mc.total();

ScoringTable t;
int score = t.dealerSelfDrawn(r.doubling_factor, minipoints);
```

## Scoring Tables

판수와 부수를 이용해 기본점수를 구합니다.

> ![][latex]

만간 이상의 경우 미리 정해진 기본점수를 사용합니다.

> | 만간 | 하네만 | 배만 | 삼배만 | 역만 |
> | ---: | ---: | ---: | ---: | ---: |
> | 2000 | 3000 | 4000 | 6000 | 8000 |

친과 자, 론과 쯔모에 따라 배율을 결정하고 100자리에서 올려 최종 지불점수를 결정합니다.

- 친 론: x6
- 자 론: x4
- 친 쯔모: x2
- 자 쯔모: x1, x2

[latex]: image/latex-basic-points.png


## Minipoints

부수를 계산합니다. 기본부수는 20부터 시작합니다. 

- 기본부 20

화료방식에 따라 부수를 추가합니다. 핑후의 경우 쯔모 부수를 받지 않습니다.

- 멘젠 론 +10
- 쯔모 +2 (핑후제외)

대기형태에 따라 부수를 추가합니다. 
여러형태의 대기로 해석이 가능할 경우, 판수가 가장 높은 대기로 계산합니다.

- 변짱 +2
- 간짱 +2
- 단기 +2

머리의 형태로 부수를 추가합니다.

- 역패 +2
- 연풍패 +4

몸통의 형태로 부수를 추가합니다.

>|       | 밍커 | 안커 | 밍깡 | 안깡 |
>| ----- | --: | --: | --: | --: |
>| 중장패 |  +2 |  +4 |  +8 | +16 |
>| 요구패 |  +4 |  +8 | +16 | +32 |

부수를 모두 더한 후, 10자리에서 올립니다.
단, 치또이의 경우 특수한 역으로 올림없이 25부를 갖습니다.

- 치또이 25부

**추가 규칙**

최종결과가 20부인 경우 핑후-쯔모를 제외하고 30부로 올립니다.
20부 취급에 대한 지역규칙 중, 많은 게임이 사용하는 쿠이핑은 30부로 취급을 기본 적용합니다.  


## Winning Hands

준비중입니다.


## Licensing

This project is licensed under the terms of [the MIT licnese][license].
