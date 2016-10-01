set(scorer_src
	all-green-recognizer.cpp
	doubling-factor-counter.cpp
	doubling-factor-table.cpp
	dragons-recognizer.cpp
	flush-recognizer.cpp
	identical-sequences-recognizer.cpp
	meld.cpp
	minipoint-counter.cpp
	no-points-hand-recognizer.cpp
	pair.cpp
	pattern-computer.cpp
	pattern-functor.cpp
	pattern-recognizer.cpp
	player-hand.cpp
	scoring-table.cpp
	seven-pairs-recognizer.cpp
	state-recognizer.cpp
	straight-recognizer.cpp
	terminal-or-honor-recognizer.cpp
	three-colour-triplets-recognizer.cpp
	tile-functor.cpp
	tile-holder.cpp
	triplets-or-quads-recognizer.cpp
	value-tiles-recognizer.cpp
	winds-recognizer.cpp
	wining-hand-collator.cpp
	wining-state.cpp

	all-green-recognizer.h
	doubling-factor-table.h
	dragons-recognizer.h
	flush-recognizer.h
	identical-sequences-recognizer.h
	meld.h
	no-points-hand-recognizer.h
	pair.h
	pattern-computer.h
	pattern-recognizer.h
	seven-pairs-recognizer.h
	state-recognizer.h
	straight-recognizer.h
	terminal-or-honor-recognizer.h
	three-colour-triplets-recognizer.h
	tile-holder.h
	triplets-or-quads-recognizer.h
	value-tiles-recognizer.h
	winds-recognizer.h
	wining-hand-collator.h
)

set(scorer_inc	
	doubling-factor-counter.h
	doubling-factor-report.h
	minipoint-counter.h
	pattern-define.h
	pattern-functor.h
	player-hand.h
	scoring-table.h
	tile-define.h
	tile-functor.h
	wining-hand.h
	wining-state.h	
)

add_library(riichi-mahjong-scorer STATIC ${scorer_src} ${scorer_inc})
install(FILES ${scorer_inc} DESTINATION include)
install(TARGETS riichi-mahjong-scorer DESTINATION lib)
