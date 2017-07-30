if __name__ == "__main__":

    cases = input()
    cases = int(cases)

    for case in range(cases):
        papers_and_names = input()
        papers_and_names = papers_and_names.split()
        papers = int(papers_and_names[0])
        names = int(papers_and_names[1])
        infinity = papers + 10

        authors_erdos = {"Erdos, P.": 0}
        proc_papers = []

        for paper in range(papers):
            paper = input()
            paper = paper.split(":")[0]

            authors = paper.split(",")
            authors = [(surname + ',' + name).strip() for surname,name in zip(authors[::2], authors[1::2])]
            proc_papers.append(authors)
            #initialize all possible base cases in one pass
            for author in authors:
                erdos = False
                if author == "Erdos, P.":
                    erdos = True
                else:
                    authors_erdos[author] = 1 if erdos else infinity

        for n in range(papers + 1):
            #print("Searching erdos {} coauthors".format(n))
            for (author, en) in authors_erdos.items():
                #print("Doing {}".format((author, en)))
                if en == n:
                    for paper in proc_papers:
                        if author in paper:
                            for coauthor in paper:
                                if authors_erdos[coauthor] > n + 1:
                                    authors_erdos[coauthor] = n + 1
        
        print("Scenario {}".format(case + 1))

        for _ in range(names):
            name = input()
            if name not in authors_erdos.keys():
                print("{} infinity".format(name))
            else:
                print("{} {}".format(name, authors_erdos[name] if authors_erdos[name] < 14 else "infinity"))

        #if case != cases - 1:
        #    input()

