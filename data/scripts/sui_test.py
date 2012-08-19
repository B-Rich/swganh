from swgpy.app import SWGKernel
from swgpy.sui import SUIService, SUIWindow, InputTrigger, ListBoxType, MessageBoxType, InputBoxType, ResultList, EventResultList, PythonCallback

def sendMessageBox(kernel, player_id):
    sui_service = kernel.service_manager().sui_service()
    owner = kernel.service_manager().simulation_service().findObjectById(player_id)

    #Create the window
    window = sui_service.CreateMessageBox(MessageBoxType.okcancel, ResultList('WARNING OMG!', 'PROBLEMS, ISSUES, WTF!'), owner)

    #Send it to the owner
    sui_service.OpenSUIWindow(window)

def listBoxCallback(object, event_type, result_list):
    print(object.id)	
    print(event_type)
    print(result_list)
    for i in range(len(result_list)):
        print(result_list[i])        
        ##print(r)
    
def sendListBox(kernel, player_id):
    sui_service = kernel.service_manager().sui_service()
    owner = kernel.service_manager().simulation_service().findObjectById(player_id)

    #Create the window
    result_list = EventResultList()
    result_list.extend( ['Woot', 'Lol', 'Omg'] )
    window = sui_service.CreateListBox(ListBoxType.okcancel, 'List Title', 'This is a list', result_list, owner)

    #Subscribe to some properties of the remote window
    returned_props = ResultList()
    returned_props.extend( ["List.lstList:SelectedRow", "bg.caption.lblTitle:Text", "this:otherPressed"] )
    window.SubscribeToEventCallback(0, "", InputTrigger.ok, returned_props, PythonCallback('sui_test', 'listBoxCallback')	)
    window.SubscribeToEventCallback(1, "", InputTrigger.cancel, returned_props, PythonCallback('sui_test', 'listBoxCallback')	)

    #Send it to the owner
    sui_service.OpenSUIWindow(window)
    
def inputBoxCallback(object, event_type, result_list):
    pass
    
def sendInputBox(kernel, player_id):
    sui_service = kernel.service_manager().sui_service()
    owner = kernel.service_manager().simulation_service().findObjectById(player_id)

    #Create the window
    window = sui_service.CreateInputBox(InputBoxType.okcancel, 'Input Title', 'This is an input', 50, owner)

    #Subscribe to some properties of the remote window
    returned_props = ResultList()
    returned_props.extend(["txtInput:LocalText"])
    #window.SubscribeToEventCallback(1, "", InputTrigger.ok, 

    #Send it to the owner
    sui_service.OpenSUIWindow(window)
    
#sui_test.sendMessageBox(kernel, 8589934603)
#sui_test.sendListBox(kernel, 8589934649)
#sui_test.sendInputBox(kernel, 8589934603)