/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

/**
 *
 * @author Alexander
 */
public class UISimpleMessage extends UIMessage {
    
    /**
     * Основной конструктор
     * @param sender Отправитель
     * @param receiver Получатель
     */
    public UISimpleMessage(UILifeLine sender, UILifeLine receiver ){
        m_sender = sender;
        m_receiver = receiver;
    } 
}
