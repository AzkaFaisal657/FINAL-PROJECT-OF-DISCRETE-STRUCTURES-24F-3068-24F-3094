# FAST University – Discrete Structures University System  

This repository contains a full-featured university management system built entirely around discrete mathematics concepts for the FAST University Discrete Structures course. The system models courses, students, faculty, prerequisites, and resources, and uses formal discrete math techniques to validate every operation — from enrollment to scheduling to conflict detection.

### What It Does 

- Generates all valid course-taking sequences respecting prerequisites  
- Verifies deep prerequisite chains with strong mathematical induction  
- Produces formal, step-by-step natural deduction proofs for enrollment eligibility  
- Implements a working propositional logic engine (modus ponens, syllogism etc.)  
- Models prerequisites as partial orders and student cohorts as equivalence relations  
- Checks injectivity/surjectivity/bijectivity of assignments (faculty ↔ courses, etc.)  
- Forms project groups and lab sessions using exact combinations and permutations  
- Detects all conflicts: credit overload, missing prereqs, room capacity, teaching load  
- Scales efficiently with memoization and proper algorithms  
- Includes a modern graphical interface built with SFML 2.6 (bonus GUI feature)  
- Loads/saves all data from text files and includes sample datasets

### Discrete Math Topics Covered

| Topic                     | Used For                                  |
|---------------------------|-------------------------------------------|
| Strong Induction          | Prerequisite chain verification           |
| Propositional Logic       | Rule engine & inference                   |
| Proof Techniques          | Automated natural deduction proofs        |
| Partial Orders            | Prerequisite dependencies                 |
| Equivalence Relations     | Schedule grouping & conflict detection    |
| Functions & Properties    | Assignment validity (injective, etc.)     |
| Combinations / Permutations | Group formation & seating                 |
| Set Operations           | Overlap & subset analysis                 |
| Graph Algorithms          | Cycle detection & topological ordering    |

### Tech Stack

- C++17 (pure standard library + SFML)  
- SFML 2.6 – for the clean, responsive GUI  
- Modular OOP design   
- No external dependencies beyond SFML

### Project Structure
```
src                 → all .h and .cpp files (one per module)
modules              → discrete math implementations
data/                 → sample courses.txt, students.txt, etc.
gui                  → SFML-based interface code
```

### Build & Run

```bash
# Linux / macOS
git clone <repo>
cd fast-university-discrete-system
mkdir build && cd build
cmake ..          # links SFML automatically if installed
make -j4
./UniversitySystem
```

Windows: open the Visual Studio solution, build, and run.

### Status

Fully working • No known crashes • All modules integrated • GUI included .

**FAST University – Discrete Structures – Fall 2025**  
