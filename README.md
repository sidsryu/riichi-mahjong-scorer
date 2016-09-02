# riichi-mahjong-scorer

[![license](https://img.shields.io/github/license/mashape/apistatus.svg?maxAge=2592000)][license]

Japanese mahjong scorer in c++14

[license]: https://github.com/sidsryu/riichi-mahjong-scorer/blob/master/LICENSE 


## About Riichi Mahjong Scorer

리치마작 계산기입니다.

완성된 손패에서 판수와 부수를 알아냅니다.
오른 방식에 따라 지불해야하는 점수를 계산합니다.

추가 목표로 텐파이 상태 확인 및 대기패 찾기 기능이 들어갑니다.


## Goal

v1.0 목표

- [x] 점수 계산하기
- [ ] 부수 계산하기
- [ ] 판수 계산하기

v2.0 목표

- [ ] 텐파이 확인하기
- [ ] 대기패 찾기


## Scoring Tables

판수와 부수를 이용해 기본점수를 구합니다.

![][latex]

만간 이상의 경우 미리 정해진 기본점수를 사용합니다.

| 만간 | 하네만 | 배만 | 삼배만 | 역만 |
| ---- | ---- | ---- | ---- | ---- |
| 2000 | 3000 | 4000 | 6000 | 8000 |

친과 자, 론과 쯔모에 따라 배율을 결정하고 100자리에서 올려 최종 지불점수를 결정합니다.

- 친 론: x6
- 자 론: x4
- 친 쯔모: x2
- 자 쯔모: x1, x2

[latex]: http://www.sciweavers.org/tex2img.php?eq=basic%5C_point%20%3D%20fu%20%20%5Ctimes%202%20%5E%20%7B%282%20%2B%20han%29%7D%0A&bc=White&fc=Black&im=png&fs=12&ff=arev&edit=0


## Minipoints

부수를 계산합니다.

## Winning Hands

판수를 계산합니다.

## Licensing

This project is licensed under the terms of [the MIT licnese][license].
