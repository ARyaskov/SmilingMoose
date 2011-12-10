/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.*;


/**
 * Абстрактный класс сообщения от одной линии жизни к другой.
 * @author Alexander
 */
abstract public class UIMessage extends SceneItem {
    
    /** Линия жизни - отправитель. */
    protected UILifeLine m_sender;
    
    /** Линия жизни - получатель */ 
    protected UILifeLine m_receiver;
    
    /** Длина линии жизни. */
    protected int m_length;
    
    /** Текст сообщения */
    protected int textX;
    
    /** Фокус у отправителя */
    public UIFocusControl m_focusSender;
    
    /** Фокус у получателя */
    public UIFocusControl m_focusReceiver;
            
    /**
     * Запросить отправителя.
     * @return объект ЛЖ
     */
    public UILifeLine getSender(){
        return m_sender;
    }
    
    /**
     * Запросить получателя.
     * @return объект ЛЖ
     */
    public UILifeLine getReceiver(){
        return m_receiver;
    }
    
    /**
     * Запросить длину сообщения
     * @return Длина сообщения
     */
    public int getLength(){
        return m_length;
    }   
    
    public int getTextX(){
        return textX;
    }
    
}
