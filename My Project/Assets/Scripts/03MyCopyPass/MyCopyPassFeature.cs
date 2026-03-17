using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.Rendering.Universal;

public class MyCopyPassFeature : ScriptableRendererFeature
{
    private MyCopyPass m_CopyPass;

    [SerializeField]
    private RenderPassEvent _renderPassEvent;

    // se llama a esto cada vez que se cambia algo (incluyendo en su creación)
    public override void Create()
    {
        m_CopyPass = new MyCopyPass();
        m_CopyPass.renderPassEvent = _renderPassEvent;
    } 

    // se llama una vez por frame
    public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)
    {
        renderer.EnqueuePass(m_CopyPass);
        // en el frame debugger aparece la etapa copy pass
    }
}