package service;

public class EmailServiceImpl implements MessageService {

  @Override
  public void sendMessage(String msg, String receiver) {
    System.out.println("Email sent to " + receiver + " with message: " + msg);
  }

}
