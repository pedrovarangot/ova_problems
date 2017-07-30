
def calculate_erdos_conex(authors_erdos, authors_erdos_2, authors_coauthors):
    next_authors = {}
    while True:
        for author, erdos in authors_erdos.items():
            if author not in authors_erdos_2.keys() or authors_erdos_2[author] > erdos:
                authors_erdos_2[author] = erdos
            for coauthor in authors_coauthors[author]:
                if coauthor not in authors_erdos_2.keys() or authors_erdos_2[coauthor] > erdos + 1:
                    authors_erdos_2[coauthor] = erdos + 1
                    next_authors[coauthor] = erdos + 1
        if next_authors != {}:
            break

if __name__ == "__main__":

    cases = input()
    cases = int(cases)

    for case in range(cases):
        papers_and_names = input()
        papers_and_names = papers_and_names.split()
        papers = int(papers_and_names[0])
        names = int(papers_and_names[1])

        authors_coauthors = {}
        proc_papers = []

        for paper in range(papers):
            paper = input()
            paper = paper.split(".:")[0]

            authors = paper.split("., ")
            authors = [author + "." for author in authors]
            proc_papers.append(authors)
            for author in authors:
                if author not in authors_coauthors.keys():
                    authors_coauthors[author] = set(authors)
                else:
                    authors_coauthors[author].update(authors)
       
        authors_erdos = {"Erdos, P.": 0}
        for author in authors_coauthors["Erdos, P."]:
            authors_erdos[author] = 1
        authors_erdos_2 = {}
        if names > 0:
            calculate_erdos_conex(authors_erdos, authors_erdos_2, authors_coauthors)

        print("Scenario {}".format(case + 1))

        for _ in range(names):
            name = input()
            if name not in authors_erdos_2.keys():
                print(name + " infinity")
            else:
                print(name + ' ' + (str(authors_erdos_2[name])))

        #if case != cases - 1:
        #    input()



