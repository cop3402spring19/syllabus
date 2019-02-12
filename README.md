# COP-3402 Systems Software Syllabus

- Spring 2019
- Section 1
- University of Central Florida
- Prerequisite(s): CDA 3103C and COP 3502C each with a grade of C (2.0) or better.

## Personnel

- Instructor
    - [Paul Gazzillo](https://paulgazzillo.com) [paul.gazzillo@ucf.edu](mailto:paul.gazzillo@ucf.edu)
- GTAs
    - Sharare Zehtabian [sharare.zehtabian@knights.ucf.edu](mailto:sharare.zehtabian@knights.ucf.edu)
    - Necip Yildiran [yildiran@knights.ucf.edu](mailto:yildiran@knights.ucf.edu)

## Office Hours

- Mondays 1:00pm-2:00pm (Sharare, HEC-315)
- Mondays 2:00pm-3:00pm (Paul, HEC-239)
- Tuesdays 11:00am-12:00pm (Necip, R1-368)
- Wednesdays 1:00pm-2:00pm (Sharare, HEC-315)
- Thursdays 10:00am-11:00am (Necip, R1-368)
- Fridays 10:00am-11:00am (Paul, HEC-239)
- or by appointment as necessary

### Exceptions

- 02/21 Thursday, cancelled

## Schedule

Class: Tuesday/Thursday 12:00PM-1:15PM CSB-0101

Semester: 01/07-04/30

Break: week of 03/11, no class, lab, or office hours.

Labs:

- Thursday 1:30PM-2:20PM HEC-0104
- Thursday 2:30PM-3:20PM CB2-O204 
- Thursday 3:30PM-4:20PM BA2-0207
- Thursday 4:30PM-5:20PM BA2-0208

_All dates in year of semester, times in UCF's time zone._

### Lecture Schedule

| Week  | Tuesday Lecture                                                     | Thursday Lecture                                     | HW | Dragon Book |
|-------|---------------------------------------------------------------------|------------------------------------------------------|-------------------|----------|
| 01/08 | Course overview                                                     | Tools                                                | None | Chapter 2 |
| 01/15 | PL/0 variant programming language                                   | Regular expressions, Project 1 announcement          | None | 3.1-3.3
| 01/22 | Automata                                                            | Lexing and ASCII encoding                            | HW1 regex/dfa | 3.4-3.7 |
| 01/29 | Grammars, Project 1 due, Project 2 announcement                     | Top-down parsing                                     | HW2 CFGs/languages | 4.1-4.4 |
| 02/05 | ASTs                                                                | Bottom-up parsing                                    | HW3 draw ASTs | 2.5.1, 3.5.1, 4.4-4.6 |
| 02/12 | Types, Project 2 due, Project 3 announcement                        | Type-checking: symbol tables and declarations        | HW4 LR parsing | 6.5 |
| 02/19 | Type-checking: expressions and statements                           | Compiler front-end review and Q&A                    | HW5 type-check some ASTs | (same) |
| 02/26 | P-code machine, Project 3 due, Project 4 announcement               | Functions                                            | HW6 evaluate p-code | 7.1-7.3 |
| 03/05 | Code generation: functions, Project 4 due, Project 5 announcement   | Code generation: expressions                         | HW7 accessing functions/vars | 8.10, 6.2-6.4 |
| 03/12 | (break)                                                             | (break)                                              | None | None |
| 03/19 | Code generation: expressions                                        | Code generation: statements, Project 6 announcement  | HW8 codegen expression | 6.6-6.7 |
| 03/26 | Code generation: everything                                         | Compiler back-end review and Q&A                     | HW9 codegen statements | (same) |
| 04/02 | Assembly, object files, linking, and loading, Project 5 due         | Optimization                                         | None | None |
| 04/09 | Program analysis                                                    | Software security                                    | HW10 control/data flow | None |
| 04/16 | Final review, Project 6 due                                         | Final review                                         | None | None |

_All readings are chapters and sections (inclusive) from the Dragon book (Compilers: Principles, Techniques, & Tools, Second Edition)_

### Due Dates

All homework is due _**by 1:30pm on Thursdays before the labs**_

All projects are due on _**the Tuesday morning before class at 02:00AM**_

- Project 1 Tuesday morning 01/29 02:00AM
- Project 2 Tuesday morning 02/12 02:00AM
- Project 3 Tuesday morning 02/26 02:00AM
- Project 4 Tuesday morning 03/05 02:00AM
- Project 5 Tuesday morning 04/02 02:00AM
- Project 6 Tuesday morning 04/16 02:00AM

Projects may be turned in late for a 1pt deduction per project.  _**The final deadline for all late project submissions is Tuesday morning 04/23 02:00AM**_, one week after the project 6 deadline.

### Final Exam

Thursday 04/25 10:00AM-12:50PM CSB-0101

## Grading

- 45% Programming project

  Each student produces their own complete compiler and p-code interpreter.

  - 6pt Project 1 - lexer
  - 9pt Project 2 - parser
  - 8pt Project 3 - typechecker
  - 5pt Project 4 - p-code machine
  - 9pt Project 5 - code generation (functions and variables)
  - 6pt Project 6 - code generation (expressions and statements)
  - 2pt for a complete, working compiler
  
  For each project, 1pt when the program compiles and there is
  evidence of effort.  Remaining points given based on how many test
  cases passed.  Minus 1pt for each project that is late.  You can
  resubmit until the late due date to be regraded, but still lose the
  1pt for lateness.

  - Warning: each phase depends on the previous

      To avoid lost points on later projects due to incomplete work on
      previous projects, use the given precompiled binaries.  E.g., if
      your parser is broken, use the given parser.o and continue
      working on the later parts of the program.
      
      - lexer: depends on no previous phases
      - parser: use the given lexer.o to work on the parser
      - typechecker: use the given parser.o to work on the typechecker
      - p-code: depends on no previous phases
      - code generation: use the given parser.o, typechecker.o, and vm.o, only typesafe programs will be tested
          - functions and variables: no statements will be tested (except those given and required)
          - expressions and statements: functions or variables will be tested (except those given)
      
- 25% Homework

    Assigned via webcourses.  Roughly 8-12 small homeworks.  Useful for completing programming
    projects.  Useful as final exam preparation.  Leniently graded.  0pt
    for late homework.  Lowest two homeworks dropped.
    Graded based on effort: 1pt for attempted multiple choice problems; 2pt for attempted open-ended questions with authentic effort, 1pt for half-hearted attemptes.  0pt for any missing answers.

- 30% Final

- +5% Discretionary and bonus points (participation, effort, etc).

### Letter Grades

A >= 90%, B+ >= 87%, B >= 80%, C+ >= 77%, C >= 70%, D >= 60%, F < 60%. (minuses may be used in some cases)

## Course Info

### Description

Design and development compilers, virtual machine interpreters,
assemblers, linkers, and loaders. Additionally, basic operating
systems will be covered as well as brief introductions to advanced
topics such as optimization, software security, and program analysis.

### Learning Outcomes

This course will provide students an understanding of systems software
tools, in particularly the compiler and other tools for processing and
executing programming languages.  Student will learn both the big
picture view of these tools as well as the details of their
development.  Students will gain both conceptual and practical
understanding of the mechanics of these tools.  The following include
motivational benefits of such study:

  - To understand well your development tools and be a better engineer
  - To work on large, complex piece of software and gain experience with
    - modularity, apis and invariants
    - incremental improvement
  - To think formally about algorithms
  - To think practically about working with data structures
  - To think about invariants, i.e., pre and post conditions, in large software products.
  - To use real-world development tools

## Course Materials

### Recommended

- Compilers: Principles, Techniques, & Tools, Second Edition by Alfred V. Aho, Monica S. Lam, Ravi Sethi, and Jeffrey D. Ullman. Addison Wesley, 2007

### Supplementary

- Advanced Compiler Design and Implementation  by Steven Muchnich. Morgan Kaufman, 1997
- Modern Compiler Implementation in C by Andrew Appel. Cambridge University Press, 1998
- Compiler Construction: Principles and Practice by Kenneth C. Louden, PWS, 1997
- Concepts of Programming Languages, 8th Edition by Robert W. Sebesta.  Addison Wesley, 2010.

## Core Policy Statements

### Academic Integrity

The Center for Academic Integrity (CAI) defines academic integrity as
a commitment, even in the face of adversity, to five fundamental
values: honesty, trust, fairness, respect, and responsibility. From
these values flow principles of behavior that enable academic
communities to translate ideals into action.
<http://academicintegrity.org/>

UCF Creed: Integrity, scholarship, community, creativity, and excellence are the core values that guide our conduct, performance, and decisions.

1. Integrity: I will practice and defend academic and personal honesty.

2. Scholarship: I will cherish and honor learning as a fundamental purpose of my membership in the UCF community.

3. Community: I will promote an open and supportive campus environment by respecting the rights and contributions of every individual.

4. Creativity: I will use my talents to enrich the human experience.

5. Excellence: I will strive toward the highest standards of performance in any endeavor I undertake.

The following definitions of plagiarism and misuse of sources come
from the Council of Writing Program Administrators
<http://wpacouncil.org/node/9> and have been adopted by UCF's
Department of Writing & Rhetoric.

#### Plagiarism
In an instructional setting, plagiarism occurs when a writer deliberately uses someone else's language, ideas, or other original (not common-knowledge) material without acknowledg­ing its source. This definition applies to texts published in print or on-line, to manuscripts, and to the work of other student writers.

#### Misuse of Sources
A student who attempts (even if clumsily) to identify and credit his or her source, but who misuses a specific citation format or incorrectly uses quotation marks or other forms of identifying material taken from other sources, has not plagiarized. Instead, such a student should be considered to have failed to cite and document sources appropri­ately.

#### Responses to Academic Dishonesty, Plagiarism, or Cheating
UCF faculty members have a responsibility for your education and the value of a UCF degree, and so seek to prevent unethical behavior and when necessary respond to infringements of academic integrity. Penalties can include a failing grade in an assignment or in the course, suspension or expulsion from the university, and/or a "Z Designation" on a student's official transcript indicating academic dishonesty, where the final grade for this course will be preceded by the letter Z. For more information about the Z Designation, see <http://goldenrule.sdes.ucf.edu/zgrade>.

For more information about UCF's Rules of Conduct, see <http://www.osc.sdes.ucf.edu/>.

#### Unauthorized Use of Class Materials
There are many fraudulent websites claiming to offer study aids to students but are actually cheat sites. They encourage students to upload course materials, such as test questions, individual assignments, and examples of graded material. Such materials are the intellectual property of instructors, the university, or publishers and may not be distributed without prior authorization. Students who engage in such activity are in violation of academic conduct standards and may face penalties.

#### Unauthorized Use of Class Notes
Faculty have reported errors in class notes being sold by third parties, and the errors may be contributing to higher failure rates in some classes. The following is a statement appropriate for distribution to your classes or for inclusion on your syllabus:

Third parties may be selling class notes from this class without my authorization. Please be aware that such class materials may contain errors, which could affect your performance or grade. Use these materials at your own risk.

#### In-Class Recording Policy
Outside of the notetaking and recording services offered by Student Accessibility Services, the creation of an audio or video recording of all or part of a class for personal use is allowed only with the advance and explicit written consent of the instructor. Such recordings are only acceptable in the context of personal, private studying and notetaking and are not authorized to be shared with anyone without the separate written approval of the instructor.

### Course Accessibility Statement 
The University of Central Florida is committed to providing access and inclusion for all persons with disabilities. This syllabus is available in alternate formats upon request. Students with disabilities who need specific access in this course, such as accommodations, should contact the professor as soon as possible to discuss various access options. Students should also connect with Student Accessibility Services (Ferrell Commons, 7F, Room 185, sas@ucf.edu, phone (407) 823-2371). Through Student Accessibility Services, a Course Accessibility Letter may be created and sent to professors, which informs faculty of potential access and accommodations that might be reasonable.

### Campus Safety Statement
Emergencies on campus are rare, but if one should arise in our class, we will all need to work together. Everyone should be aware of the surroundings and familiar with some basic safety and security concepts. 

- In case of an emergency, dial 911 for assistance. 

- Every UCF classroom contains an emergency procedure guide posted on a wall near the door. Please make a note of the guide's physical location and consider reviewing the online version at <http://emergency.ucf.edu/emergency_guide.html>.

- Familiarize yourself with evacuation routes from each of your classrooms and have a plan for finding safety in case of an emergency. (Insert class-specific details if appropriate)

- If there is a medical emergency during class, we may need to access a first aid kit or AED (Automated External Defibrillator). To learn where those items are located in this building, see <http://www.ehs.ucf.edu/AEDlocations-UCF> (click on link from menu on left). (insert class specific information if appropriate)

- To stay informed about emergency situations, sign up to receive UCF text alerts by going to my.ucf.edu and logging in. Click on "Student Self Service" located on the left side of the screen in the tool bar, scroll down to the blue "Personal Information" heading on your Student Center screen, click on "UCF Alert", fill out the information, including your e-mail address, cell phone number, and cell phone provider, click "Apply" to save the changes, and then click "OK."

- If you have a special need related to emergency situations, please speak with me during office hours.

- Consider viewing this video (<https://youtu.be/NIKYajEx4pk>) about how to manage an active shooter situation on campus or elsewhere.

### Deployed Active Duty Military Students
If you are a deployed active duty military student and feel that you may need a special accommodation due to that unique status, please contact your instructor to discuss your circumstances.
