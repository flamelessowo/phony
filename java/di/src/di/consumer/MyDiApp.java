package consumer;

import service.MessageService;

public class MyDiApp implements Consumer {

  private MessageService service;

  public MyDiApp(MessageService svc) {
    this.service = svc;
  }
  
  @Override
  public void processMessages(String msg, String rcv) {
    this.service.sendMessage(msg, rcv);
  }
}
