# parser_.py
from bs4 import BeautifulSoup

def parse_html(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        html = file.read()
    soup = BeautifulSoup(html, 'html.parser')
    title = soup.title.string if soup.title else 'No Title Found'
    return title
