/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import bbj.virtualobjects.FreeComment;
import bbj.virtualobjects.LifeLine;
import bbj.virtualobjects.Message;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JTextField;

/**
 * Класс, реализующий текстовое поле для ввода данных
 * @author Alexander
 */
public class EditField extends JTextField implements KeyListener{

    SceneItem m_item;   // Родительский элемент сцены
    int m_type;
            
    /**
     * Конструктор с параметром
     * @param item Элемент сцены
     */
    EditField(SceneItem item){
        
        m_item = item;
        

        this.setBounds(5, 5, 120, 40);
        
        String currentText = item.getText();
        this.setText(currentText);
        this.addKeyListener(this);
        m_type = -1;
        
        if (m_item.toString().contains("UIFreeComment")) {
            m_type = 0;
        }
        else if (m_item.toString().contains("UIRectLifeLine")) {
            m_type = 1;
        }
        else if(m_item.toString().contains("UIActorLifeLine")) {
            m_type = 2;
        }
        else if (m_item.toString().contains("UISimpleMessage")) {
            m_type = 3;
            setBounds(105, 5, 120, 40);
        }
        
        m_item.add(this);
        this.setVisible(true);
        this.grabFocus();
    }
    
    /**
     * Обработка события нажатия клавиш
     * @param e Данное событие
     */
    @Override
    public void keyTyped(KeyEvent e) {
        if (e.getKeyChar() == KeyEvent.VK_ENTER){   // Если нажали Enter
            
            // Изменить текст
            String newText = this.getText();
            m_item.setText(newText);
            
            for (int i = 0; i < bbj.BBJ.app.getScene().getModel().size(); i++) {
                if (bbj.BBJ.app.getScene().getModel().getObject(i).getId() == m_item.id) {
                    if (bbj.BBJ.app.getScene().getModel().getObject(i).getClass() == FreeComment.class) {
                        bbj.BBJ.app.getScene().getModel().getObject(i).setDescription(m_item.getText());
                        break;
                    } else if (bbj.BBJ.app.getScene().getModel().getObject(i).getClass() == LifeLine.class) {
                        ((LifeLine)bbj.BBJ.app.getScene().getModel().getObject(i)).setName(m_item.getText());
                        break;
                    } else {
                        ((Message)bbj.BBJ.app.getScene().getModel().getObject(i)).setName(m_item.getText());
                        break;
                    }
                }
            }
            
            if (m_type==0)
                m_item.setToolTipText("Свободный комментарий: " + newText);
            else if (m_type == 1)
                m_item.setToolTipText("Линия жизни: " + newText);
            else if (m_type == 2)
                m_item.setToolTipText("Исполнитель: " + newText);
            else if (m_type == 3)
                m_item.setToolTipText("Сообщение: " + newText);
            
            m_item.updateUI();
            this.setVisible(false);
            m_item.remove(this);
        }
        else if (e.getKeyChar() == KeyEvent.VK_ESCAPE){ // Если нажали Escape
            this.setVisible(false);
            m_item.remove(this);
            m_item.updateUI();
        }
            
    }

    @Override
    public void keyPressed(KeyEvent e) {
        
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }   
}
