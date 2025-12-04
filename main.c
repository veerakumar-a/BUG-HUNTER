import React, { useState, useEffect } from 'react';
import { Trophy, Target, Clock, Star, AlertCircle } from 'lucide-react';

const BugHunterArena = () => {
  const [level, setLevel] = useState(1);
  const [score, setScore] = useState(0);
  const [timeLeft, setTimeLeft] = useState(60);
  const [gameState, setGameState] = useState('menu'); // menu, playing, complete
  const [selectedLine, setSelectedLine] = useState(null);
  const [attempts, setAttempts] = useState(0);
  const [feedback, setFeedback] = useState('');

  const bugChallenges = [
    {
      level: 1,
      title: "Missing Semicolon",
      language: "JavaScript",
      code: [
        "function greet(name) {",
        "  console.log('Hello, ' + name)",
        "  return true;",
        "}"
      ],
      bugLine: 1,
      explanation: "Missing semicolon at the end of console.log statement",
      fix: "  console.log('Hello, ' + name);",
      difficulty: "Easy"
    },
    {
      level: 2,
      title: "Undefined Variable",
      language: "Python",
      code: [
        "def calculate_total(items):",
        "    total = 0",
        "    for item in items:",
        "        totl += item.price",
        "    return total"
      ],
      bugLine: 3,
      explanation: "Variable name 'totl' is misspelled (should be 'total')",
      fix: "        total += item.price",
      difficulty: "Easy"
    },
    {
      level: 3,
      title: "Off-by-One Error",
      language: "JavaScript",
      code: [
        "function getLastElement(arr) {",
        "  return arr[arr.length];",
        "}",
        "",
        "const nums = [1, 2, 3];"
      ],
      bugLine: 1,
      explanation: "Array index should be arr.length - 1, not arr.length",
      fix: "  return arr[arr.length - 1];",
      difficulty: "Medium"
    },
    {
      level: 4,
      title: "Infinite Loop",
      language: "JavaScript",
      code: [
        "let count = 0;",
        "while (count < 10) {",
        "  console.log(count);",
        "  count--;",
        "}"
      ],
      bugLine: 3,
      explanation: "count-- decrements instead of increments, causing infinite loop",
      fix: "  count++;",
      difficulty: "Medium"
    },
    {
      level: 5,
      title: "Wrong Comparison Operator",
      language: "JavaScript",
      code: [
        "function isEqual(a, b) {",
        "  if (a = b) {",
        "    return true;",
        "  }",
        "  return false;",
        "}"
      ],
      bugLine: 1,
      explanation: "Using assignment (=) instead of comparison (===)",
      fix: "  if (a === b) {",
      difficulty: "Medium"
    },
    {
      level: 6,
      title: "Async/Await Missing",
      language: "JavaScript",
      code: [
        "function fetchData() {",
        "  const data = await fetch('/api/data');",
        "  return data.json();",
        "}"
      ],
      bugLine: 0,
      explanation: "Function must be declared 'async' to use 'await'",
      fix: "async function fetchData() {",
      difficulty: "Hard"
    },
    {
      level: 7,
      title: "Wrong Array Method",
      language: "JavaScript",
      code: [
        "const numbers = [1, 2, 3, 4];",
        "const doubled = numbers.map((n) => {",
        "  n * 2;",
        "});",
        "console.log(doubled);"
      ],
      bugLine: 2,
      explanation: "Missing 'return' statement in arrow function",
      fix: "  return n * 2;",
      difficulty: "Hard"
    },
    {
      level: 8,
      title: "Null Reference",
      language: "JavaScript",
      code: [
        "function getUserName(user) {",
        "  return user.profile.name;",
        "}",
        "",
        "const user = { id: 1 };"
      ],
      bugLine: 1,
      explanation: "user.profile is undefined, causing null reference error",
      fix: "  return user?.profile?.name || 'Unknown';",
      difficulty: "Hard"
    }
  ];

  const currentChallenge = bugChallenges[level - 1];

  useEffect(() => {
    let timer;
    if (gameState === 'playing' && timeLeft > 0) {
      timer = setTimeout(() => setTimeLeft(timeLeft - 1), 1000);
    } else if (timeLeft === 0 && gameState === 'playing') {
      setGameState('complete');
      setFeedback('Time\'s up! Game Over.');
    }
    return () => clearTimeout(timer);
  }, [timeLeft, gameState]);

  const startGame = () => {
    setGameState('playing');
    setLevel(1);
    setScore(0);
    setTimeLeft(60);
    setAttempts(0);
    setFeedback('');
    setSelectedLine(null);
  };

  const checkBug = (lineIndex) => {
    setSelectedLine(lineIndex);
    setAttempts(attempts + 1);

    if (lineIndex === currentChallenge.bugLine) {
      const points = currentChallenge.difficulty === 'Easy' ? 100 : 
                     currentChallenge.difficulty === 'Medium' ? 200 : 300;
      const bonus = attempts === 0 ? 50 : 0;
      setScore(score + points + bonus);
      setFeedback(`✓ Correct! ${currentChallenge.explanation}`);
      
      setTimeout(() => {
        if (level < bugChallenges.length) {
          setLevel(level + 1);
          setAttempts(0);
          setFeedback('');
          setSelectedLine(null);
          setTimeLeft(timeLeft + 15);
        } else {
          setGameState('complete');
          setFeedback('🎉 Congratulations! You completed all levels!');
        }
      }, 2000);
    } else {
      setFeedback('✗ Wrong line! Try again.');
      setTimeout(() => setFeedback(''), 1500);
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-slate-900 via-purple-900 to-slate-900 text-white p-8">
      <div className="max-w-6xl mx-auto">
        {/* Header */}
        <div className="text-center mb-8">
          <h1 className="text-5xl font-bold mb-2 bg-clip-text text-transparent bg-gradient-to-r from-cyan-400 to-purple-400">
            🐛 Bug Hunter Arena
          </h1>
          <p className="text-gray-300 text-lg">Master the Art of Debugging</p>
        </div>

        {gameState === 'menu' && (
          <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-12 text-center border border-purple-500/30">
            <Target className="w-24 h-24 mx-auto mb-6 text-cyan-400" />
            <h2 className="text-3xl font-bold mb-4">Welcome, Bug Hunter!</h2>
            <p className="text-gray-300 mb-8 text-lg max-w-2xl mx-auto">
              Hunt down bugs in various code snippets. Click on the line with the bug to fix it.
              Earn points for each bug found and race against time!
            </p>
            <div className="grid grid-cols-3 gap-4 mb-8 max-w-2xl mx-auto">
              <div className="bg-slate-700/50 p-4 rounded-lg">
                <Star className="w-8 h-8 mx-auto mb-2 text-yellow-400" />
                <p className="text-sm">8 Levels</p>
              </div>
              <div className="bg-slate-700/50 p-4 rounded-lg">
                <Clock className="w-8 h-8 mx-auto mb-2 text-cyan-400" />
                <p className="text-sm">60 Seconds</p>
              </div>
              <div className="bg-slate-700/50 p-4 rounded-lg">
                <Trophy className="w-8 h-8 mx-auto mb-2 text-purple-400" />
                <p className="text-sm">High Scores</p>
              </div>
            </div>
            <button
              onClick={startGame}
              className="bg-gradient-to-r from-cyan-500 to-purple-500 px-8 py-4 rounded-lg text-xl font-bold hover:scale-105 transition-transform"
            >
              Start Hunting
            </button>
          </div>
        )}

        {gameState === 'playing' && currentChallenge && (
          <>
            {/* Stats Bar */}
            <div className="grid grid-cols-4 gap-4 mb-6">
              <div className="bg-slate-800/50 backdrop-blur-lg rounded-lg p-4 border border-cyan-500/30">
                <div className="flex items-center justify-between">
                  <span className="text-gray-400">Level</span>
                  <span className="text-2xl font-bold text-cyan-400">{level}/8</span>
                </div>
              </div>
              <div className="bg-slate-800/50 backdrop-blur-lg rounded-lg p-4 border border-purple-500/30">
                <div className="flex items-center justify-between">
                  <span className="text-gray-400">Score</span>
                  <span className="text-2xl font-bold text-purple-400">{score}</span>
                </div>
              </div>
              <div className="bg-slate-800/50 backdrop-blur-lg rounded-lg p-4 border border-yellow-500/30">
                <div className="flex items-center justify-between">
                  <Clock className="w-5 h-5 text-yellow-400" />
                  <span className="text-2xl font-bold text-yellow-400">{timeLeft}s</span>
                </div>
              </div>
              <div className="bg-slate-800/50 backdrop-blur-lg rounded-lg p-4 border border-green-500/30">
                <div className="flex items-center justify-between">
                  <span className="text-gray-400">Attempts</span>
                  <span className="text-2xl font-bold text-green-400">{attempts}</span>
                </div>
              </div>
            </div>

            {/* Challenge Card */}
            <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-8 border border-purple-500/30">
              <div className="flex justify-between items-start mb-6">
                <div>
                  <h2 className="text-3xl font-bold mb-2">{currentChallenge.title}</h2>
                  <div className="flex gap-3">
                    <span className="px-3 py-1 bg-blue-500/20 text-blue-300 rounded-full text-sm">
                      {currentChallenge.language}
                    </span>
                    <span className={`px-3 py-1 rounded-full text-sm ${
                      currentChallenge.difficulty === 'Easy' ? 'bg-green-500/20 text-green-300' :
                      currentChallenge.difficulty === 'Medium' ? 'bg-yellow-500/20 text-yellow-300' :
                      'bg-red-500/20 text-red-300'
                    }`}>
                      {currentChallenge.difficulty}
                    </span>
                  </div>
                </div>
                <AlertCircle className="w-8 h-8 text-red-400" />
              </div>

              <p className="text-gray-300 mb-6 text-lg">
                Click on the line that contains the bug:
              </p>

              {/* Code Block */}
              <div className="bg-slate-950/50 rounded-lg p-6 font-mono text-sm border border-slate-700">
                {currentChallenge.code.map((line, idx) => (
                  <div
                    key={idx}
                    onClick={() => checkBug(idx)}
                    className={`py-2 px-4 -mx-4 cursor-pointer transition-all ${
                      selectedLine === idx
                        ? idx === currentChallenge.bugLine
                          ? 'bg-green-500/20 border-l-4 border-green-400'
                          : 'bg-red-500/20 border-l-4 border-red-400'
                        : 'hover:bg-slate-800/50'
                    }`}
                  >
                    <span className="text-gray-500 mr-4">{idx + 1}</span>
                    <span className={selectedLine === idx && idx === currentChallenge.bugLine ? 'text-green-300' : 'text-gray-300'}>
                      {line}
                    </span>
                  </div>
                ))}
              </div>

              {/* Feedback */}
              {feedback && (
                <div className={`mt-6 p-4 rounded-lg ${
                  feedback.includes('✓') ? 'bg-green-500/20 border border-green-400/50' : 'bg-red-500/20 border border-red-400/50'
                }`}>
                  <p className="text-lg">{feedback}</p>
                </div>
              )}
            </div>
          </>
        )}

        {gameState === 'complete' && (
          <div className="bg-slate-800/50 backdrop-blur-lg rounded-2xl p-12 text-center border border-purple-500/30">
            <Trophy className="w-32 h-32 mx-auto mb-6 text-yellow-400" />
            <h2 className="text-4xl font-bold mb-4">Game Over!</h2>
            <p className="text-2xl text-purple-300 mb-2">Final Score: {score}</p>
            <p className="text-xl text-gray-400 mb-8">Levels Completed: {level - 1}/8</p>
            <button
              onClick={startGame}
              className="bg-gradient-to-r from-cyan-500 to-purple-500 px-8 py-4 rounded-lg text-xl font-bold hover:scale-105 transition-transform"
            >
              Play Again
            </button>
          </div>
        )}
      </div>
    </div>
  );
};

export default BugHunterArena;
