# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    # Read the team data in program's memory and add each team to LIST(it's []) 'teams'
    # Name of the file is sys.argv[1]
    # with open(sys.argv[1], "r") as file:
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            row['rating'] = int(row['rating'])
            teams.append(row)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # Run N tournament simulations (1000 TOURNAMENTS!), keep track of how many times each team wins in the counts{} dictionary
    # Uruguay 2 - Portugal 3 counts is {"Uruguay": 2, "Portugal": 3}

    # in dict 'counts[team_name] = x' will associate the key stored in 'team_name' with the value stored in 'x'
    # {key - country, value - number of TOURNAMENT WINS}
    # Use keyword 'in' to check if a dict has a particular key already. 'if "Portugal" in counts:' checks if
    # "Portugal" already has an existing value in the 'counts' dictionary

    for i in range(N):
        winner = simulate_tournament(teams)

        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # Input list of teams
    # Repeatedly simulate rounds until one team left.
    # Simulate round returns list of winners[]
    # Cannot assume number of teams in the tournament, but it's definitely power of 2

    # If x is a list, len(x) determines the length of the list
    while len(teams) > 1:
        teams = simulate_round(teams)

    # Return name of that team
    return teams[0]['team']


if __name__ == "__main__":
    main()
