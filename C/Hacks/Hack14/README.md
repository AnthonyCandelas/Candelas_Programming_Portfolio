# Hack14 - Battleship Client (C)

Name: Anthony Candelas  
Email: tsallinger2@unl.edu  
Date: 12Dec2025

## Overview
Text-based Battleship client using HTTP/JSON against `http://csce.unl.edu:8080`. Built with libcurl. Implements a hunt-target strategy that searches the board systematically and adapts when ships are hit.

## Build
```bash
cd C/Hacks/Hack14
make
```
Requires libcurl. macOS includes it; Linux may need `sudo apt-get install libcurl4-openssl-dev` or similar.

## Run
Interactive mode:
```bash
./battleship
```
Enter moves as `x y` pairs (0-9).

Auto-play mode (recommended):
```bash
./battleship --auto
```

## Implementation Details
- HTTP client using libcurl for GET/POST requests.
- Server contract: moves sent as form parameter `move={JSON}` to `/Battleship/Move`.
- Board tracking: -1 (unknown), 0 (miss), 1 (hit).
- Strategy: Checkerboard hunt phase followed by targeted neighbor search after hits.
- Detects win/loss and exits on game_status field.

## Winning Game
- Game ID: 290d68ea
- Final Score: 2
- Strategy: Hunt-target with adjacency queue for efficient ship sinking.

## Personal Writeup

**Experience using LLM:**
I use LLMs daily—across multiple models and contexts. The iterative approach of describing a problem, testing outputs, and refining based on results has become routine. LLMs help me move faster and explore more solutions, whether prototyping systems, learning new libraries, or thinking through design problems. The key is active engagement: I'm not copying answers; I'm using them as thinking partners to stress-test ideas, explore edge cases, and validate approaches. Over time, the workflow compounds as I learn what works, what doesn't, and why.

**Observations and realizations:**
What I've noticed using AI tools is that they're amplifiers, not replacements. They synthesize solutions quickly, but they don't inherently understand correctness or the full context. When people use them without validation—just copying output and shipping—results tend to be fragile. I see this in my own work: if I don't validate the logic, test edge cases, and think critically about what the tool produces, I'm just outsourcing the problem, not solving it. The real insight is that AI doesn't eliminate the need for skill; it changes how you apply it. Tools require learning and intentional use to work well. The barrier to entry is low, but actually getting good with them takes effort and iteration.

**Power vs limitations:**
*Power:* LLMs excel at rapid prototyping, learning unfamiliar APIs, generating boilerplate, and explaining concepts. For exploring new technologies and synthesizing solutions, they're invaluable. They help you think through problems faster and validate approaches at scale.

*Limitations:* They hallucinate details, miss domain-specific nuances, and lack judgment about context and correctness. They're also prone to over-engineering and don't inherently understand long-term implications. The safest approach is to use AI as a draft engine and thinking tool, not a decision engine. Validation, testing, and critical review are non-negotiable.

**Learnings and conclusions:**
The biggest lesson is that mastery—knowing when to trust the tool, when to push back, when to redesign your prompt—separates effective users from those who just copy-paste. Knowing *when to question* the output is the real skill. I've invested in AI trainings and bootcamps to understand how models think and fail. Equally important is creating safeguards and oversight mechanisms to validate outputs and guide AI systems. The quality of your engagement with the tool dictates the quality of the result. Passive use produces passive results; active, critical iteration produces better outcomes.

**Future usage of LLMs:**
I'll continue using AI tools aggressively, but carefully. Preventing smart use of these tools is a handicap to career development and adaptability. The workforce is already integrating AI; if you don't learn to use it well, you'll fall behind. The companies building these tools aren't slowing down, and neither will the economy. The path forward is education, mastery, and thoughtful integration. Those who learn the tool and use it critically will have an advantage. Those who resist or use it blindly will struggle. The key is balancing speed with validation.

**Ownership of generated code:**
This code is mine. I prompted, iterated, debugged, and validated it. The LLM didn't run autonomously—I directed every step based on feedback and testing. If you assign ownership to the platform (say, Anthropic), then Microsoft owns everything on Windows, Apple owns macOS outputs, and Nvidia owns GPU computations. That logic breaks down quickly. Ownership follows interaction and intent. I didn't purchase rights to the LLM or assign it identity; I used it as a tool. Most code and data are already discovered; what changes is authorship and formatting. We must learn to read what has been formatted. The code emerges from my decisions, my prompts, my validation, and my understanding. That makes it mine.
