import time

from secret import STUDENT_ID, PASSWORD

from selenium import webdriver
from selenium.webdriver.common.keys import Keys

# Configuration

TIME = 60 * 2
COURSES = [
    'cs311',
    #'eng314',
]


def start():
    driver = webdriver.Firefox()
    driver.implicitly_wait(30)
    driver.base_url = "https://accessplus.iastate.edu/"
    driver.verificationErrors = []
    driver.accept_next_alert = True

    return driver


def load_registration_page(driver):
    # Login
    driver.get(driver.base_url + "/frontdoor/login.jsp")
    driver.find_element_by_id("loginid").clear()
    driver.find_element_by_id("loginid").send_keys(STUDENT_ID)
    driver.find_element_by_id("pinpass").clear()
    driver.find_element_by_id("pinpass").send_keys(PASSWORD)
    driver.find_element_by_css_selector("input[name=\"login\"]").click()

    # Load Student page
    driver.find_element_by_css_selector("img[alt=\"Student Menu\"]").click()
    driver.find_element_by_xpath("//a[7]/b").click()
    driver.find_element_by_name("Continue").click()
    driver.find_element_by_name("RegTerm").click()
    driver.find_element_by_id("submit1").click()
    driver.find_element_by_id("DeptInfo").click()


def lookup_eng314(driver):
    # Look up class
    select = driver.find_element_by_id("DeptInfo")
    select.send_keys('ENGL')
    select.send_keys(Keys.RETURN)

    # Select CompSci and enter 311
    driver.find_element_by_name("R2193_CRSE").click()
    driver.find_element_by_name("R2193_CRSE").clear()
    driver.find_element_by_name("R2193_CRSE").send_keys("314")
    driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[5]/td[2]").click()
    driver.find_element_by_css_selector("input[type=\"submit\"]").click()


def eng314(driver):
    driver.find_element_by_css_selector("input[type=\"submit\"]").click()

    section1 = driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[6]/td/table/tbody/tr[2]/td[3]").text
    section2 = driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[6]/td/table/tbody/tr[8]/td[3]").text
    section3 = driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[6]/td/table/tbody/tr[10]/td[3]").text
    section4 = driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[6]/td/table/tbody/tr[12]/td[3]").text

    result = False
    if section1 != 'Closed':
        driver.find_element_by_css_selector("form[name=\"inputform\"] > input[type=\"submit\"]").click()
        result = True
    elif section2 != 'Closed':
        driver.find_element_by_xpath("(//input[@value='Add'])[4]").click()
        result = True
    elif section3 != 'Closed':
        driver.find_element_by_xpath("(//input[@value='Add'])[5]").click()
        result = True
    elif section4 != 'Closed':
        driver.find_element_by_xpath("(//input[@value='Add'])[6]").click()
        result = True

    return result


def lookup_cs311(driver):
    # Look up class
    select = driver.find_element_by_id("DeptInfo")
    select.send_keys('COM S')
    select.send_keys(Keys.RETURN)

    # Select CompSci and enter 311
    driver.find_element_by_name("R2193_CRSE").click()
    driver.find_element_by_name("R2193_CRSE").clear()
    driver.find_element_by_name("R2193_CRSE").send_keys("311")
    driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[5]/td[2]").click()
    driver.find_element_by_css_selector("input[type=\"submit\"]").click()


def cs311(driver):
    driver.find_element_by_css_selector("input[type=\"submit\"]").click()

    section1 = driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[6]/td/table/tbody/tr[2]/td[3]").text
    section2 = driver.find_element_by_xpath("//div[@id='appDiv']/table/tbody/tr[6]/td/table/tbody/tr[4]/td[3]").text

    result = False
    if section1 != 'Closed':
        driver.find_element_by_css_selector("form[name=\"inputform\"] > input[type=\"submit\"]").click()
        result = True
    elif section2 != 'Closed':
        driver.find_element_by_css_selector("tr.even > td > form[name=\"inputform\"] > input[type=\"submit\"]").click()
        result = True

    return result

if __name__ == "__main__":
    driver = start()
    load_registration_page(driver)

    status = [False] * len(COURSES)
    while False in status:
        for i, course in enumerate(COURSES):
            if status[i] is True:
                continue
            if course in locals() and ('lookup_' + course) in locals():
                locals().get('lookup_' + course)(driver)
                status[i] = locals().get(course)(driver)

                if status[i] is True:
                    print 'Successfully registered for {0}'.format(course)
                else:
                    print '{0} is still full, trying again in {1} min'.format(course, TIME / 60)

        time.sleep(TIME)
