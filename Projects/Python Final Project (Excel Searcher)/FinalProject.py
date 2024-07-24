#Tyson Keough
#200578592
#Feb 26th, 2024
#11:44 AM
#A project that checks a spread sheet and finds the policies needed
#it then takes that policies that are found and puts them into a word document

#import the needed modules
import openpyxl, re, pyinputplus as pyip, docx, time

#This is the Function that searches the sheet
def sheetChecker(nameList):
    #try this stuff
    try:    
        #load The Policy sheet
        excelSheet= openpyxl.load_workbook("C:\\Final_Project_info\\Policy_Procedure_Tracking_2023.xlsx")
        #set it as the active sheet
        sheet = excelSheet.active
        #make the row variable the max row size
        rowRange =10000
        #A list of all the columns in the excel file
        columnList = ['B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','AA','AB','AC','AD','AE']
        #for every name within the name list
        for names in range(len(nameList)):
            #create a empty list of policies
            listOfPolicies =[]
            #store the name in a variable
            name = nameList[names]
            #make a list to flip the name around into FIRST, LAST
            userNameFlip= []
            #split the name by the comma
            nameSplit = name.split(", ")
            #for each name split in nameSplit
            for namesSplit in nameSplit:
                #append it to userNameFlip
                userNameFlip.append(namesSplit)
            #Flip the name in the format firstname, lastname
            userNameFlip = userNameFlip[::-1]
            #for every row in the range from 1 to the max amount of rows + 1
            for row in range(1, rowRange + 1):
                #store the value of the cell in cellContents
                cellContents = sheet['A'+ str(row)].value
                #if the cellContents matches the name
                if cellContents == name:
                    #print that the the person was found within the list
                    print(userNameFlip[0] + ', ' + userNameFlip[1] + ' was found')
                    #store the row that the name was found in
                    clientsRow = row
                    #make a counter variable set to 0
                    counter = 0
                    #for every column within the range from 1 to the max amount of columns + 1
                    for column in columnList:
                        #store the value from the clients row and each column
                        cell = sheet[column + str(clientsRow)].value
                        #if the cell is none or blank
                        if cell == None or cell == '':
                            #store the policy 
                            policyNeeded = sheet[column + str(2)].value
                            #if the policy is none
                            if policyNeeded == None:
                                #continue
                                continue
                            #if it has a policy
                            else:
                                #add it to the list of policies
                                listOfPolicies.append(policyNeeded)
                                #add to the counter
                                counter = counter + 1
                    #Tell the user how many policies that chosen person needs to read
                    print("The Number of Polices That "+ userNameFlip[0] +', ' +userNameFlip[1] + " Needs to Read Would Be: " + str(counter))
                    #if the length of the list is greater than 0
                    if len(listOfPolicies) > 0:
                        #create a new document
                        doc =docx.Document()
                        #store the current time
                        now = time.time()
                        #make a time that is 3 weeks from the current time
                        dueTime = now + 1814400
                        #add a paragraph to the docx
                        doc.add_paragraph('Pinecrest Nursing Home')
                        #add a paragraph to the docx
                        doc.add_paragraph('3418 County Road 36,')
                        #add a paragraph to the docx
                        doc.add_paragraph('Bobcaygeon, Ontario, Canada')
                        #add a paragraph to the docx
                        doc.add_paragraph('705 - 738-2366\n')
                        #add a paragraph to the docx with the current time
                        doc.add_paragraph(str(time.ctime(now))+'\n')
                        #add the chosen name to the docx
                        doc.add_paragraph('Dear ' + userNameFlip[0] + ', ' + userNameFlip[1])
                        #add a parapgraph to the docx
                        doc.add_paragraph('The Fixing Long-Term Care Act, 2021 and Regulations require that direct care staff receive training in certain areas at orientation and annually thereafter.  In reviewing our records, you have not reviewed the following policies and procedures as required:\n')
                        #for i in the range of the length of the list of policies
                        for i in range(len(listOfPolicies)):
                            #add each policy to the docx
                            doc.add_paragraph(str(listOfPolicies[i]))
                        #add a paragraph to the docx
                        doc.add_paragraph('\nAs part of your employment you are expected to be familiar with and to follow the policies and procedures as set out by the home.')
                        #add a paragraph to the docx
                        doc.add_paragraph('Please review the Policies that are highlighted above by '+str(time.ctime(dueTime)) + ' sign and date above that you have completed your review and return this sheet to the Main Office.')
                        #add a paragraph to the docx
                        doc.add_paragraph('Failure to review the required Policies will result in a disciplinary action.')
                        #add a paragraph to the docx
                        doc.add_paragraph('Thank you for your assistance in this regard.\n')
                        #add a paragraph to the docx
                        doc.add_paragraph('\nJenelle Whalen')
                        #add a paragraph to the docx
                        doc.add_paragraph('Administrator')
                        #save the doc with the chosen users name
                        doc.save(userNameFlip[0] + ', ' + userNameFlip[1] + " Policies Needed.docx")
                        #print a prompt telling the user that a docx file has been created for the chosen user
                        print("A Word File Has Now Been Created For The Following Staff: "+ userNameFlip[0] +', ' + userNameFlip[1]+'\n')
            #if it can't find any policies for the person
            if len(listOfPolicies) == 0:
                #print a prompt telling the user that the person they were checking has no policies that they need to read
                print("There are no Policies For: " + name + ". Make Sure the Person Chosen is on the Excel Sheet\n")
        #a simple prompt to get the any key to end the program        
        input("Please Press Any Key to end the program.")
        #return 1
        return 1
    except FileNotFoundError:
        #print a message asking the user to check the excel files path
        print("Please check That the file path for the excel file is correct.")
        #return 0
        return 0
    #except a permission error
    except PermissionError:
        #tell the user to close the docx file and try again
        print("Please close the opened docx file and try again.")
        #call the userInputs function
        userInputs()
        #except a file not found error
#define the user input function
def userInputs():
    #make a empty list for all of the people the user would like to search for
    userInputList = []
    #make a counter variable
    listCounter = 0
    #while list counter is less than or equal to 1
    while not listCounter >=1:
        #use pyinputplus to ask the user to input a name where it goes LASTNAME, FIRSTNAME
        userInput = pyip.inputStr(prompt = "Please input a name in the format of LASTNAME, FIRSTNAME\n", allowRegexes =[r'^[A-Z][A-Z]*,\s[A-Z][A-Z]*$'], blockRegexes=[('.*')])
        #add users input to the empty list made earlier
        userInputList.append(userInput)
        #add 1 to the list counter
        listCounter = listCounter + 1
        #if the list counter is 1
        if listCounter == 1:
            #ask user if they would like to add another name to the search
            userResponse = pyip.inputYesNo("would you like to search for another person within this doc (yes/no)\n")
        #if they choose yes
        if userResponse == 'yes':
            #subtract 1 from the counter
           listCounter = listCounter - 1
        #else 
        else:
            #add 1 to the counter
            listCounter = listCounter + 1
    #print the sheetchecker function with the users list
    print(sheetChecker(userInputList))
    #return 1
    return 1
#call the user Inputs function and print the output
print(userInputs())
